#include "ClipsInfoModelRulemachine1_data_importer.h"
#include "callback.h"
#include "callback_internal.h"
#include <cwalk.h>
#include <dirent.h>

typedef struct s_DataFindFeasibleFiles {
	const char* filename;
	size_t l_filename;
	char* directory_path;
	DIR* opendir;
} DataFindFeasibleFiles;

typedef struct s_NextFeasibleFile {
	int err;
	char* filepath;
	const char* ext;
} NextFeasibleFile;
static NextFeasibleFile NO_NEXT_FILE = {.err = 1, .filepath = NULL};
static void release_NextFeasibleFile(NextFeasibleFile);

static int initialize_DataFindFeasibleFiles(DataFindFeasibleFiles* dfff, CallbackConfig* cfg, const char* iri);
static NextFeasibleFile DataFindFeasibleFiles_next(DataFindFeasibleFiles*);
static void release_DataFindFeasibleFiles(DataFindFeasibleFiles*);

static int get_directory_and_filename(DataFindFeasibleFiles* dfff, CallbackConfig* cfg, const char* iri);
static char* generate_directory_path(const char* basepath, const char* addiri, const char* addiri_end);
static char* load_into_memory(const char* filepath);
static char* my_join_path(const char* first, const char* second);

DataDescription CallbackConfig_get_data(CallbackConfig* cfg, const char* iri){
	DataDescription ret = {.data= NULL, .format=NULL};
	DataFindFeasibleFiles iter;
	if(0 != initialize_DataFindFeasibleFiles(&iter, cfg, iri)){
		fprintf(stderr, "ERROR CallbackConfig_get_data\n");
		return ret;
	}
	for(NextFeasibleFile x = DataFindFeasibleFiles_next(&iter);
			x.err == 0;
			x = DataFindFeasibleFiles_next(&iter))
	{
		ret.data = load_into_memory(x.filepath);
		ret.format = malloc(strlen(x.ext) + 1);
		strcpy(ret.format, x.ext);
		release_NextFeasibleFile(x);
		break;
	}
	release_DataFindFeasibleFiles(&iter);
	return ret;
}

static void release_DataFindFeasibleFiles(DataFindFeasibleFiles* x){
	x->filename = NULL;
	if(x->directory_path != NULL){
		free(x->directory_path);
		x->directory_path = NULL;
	}
	if(x->opendir != NULL){
		closedir(x->opendir);
		x->opendir = NULL;
	}
}

static int initialize_DataFindFeasibleFiles(DataFindFeasibleFiles* dfff, CallbackConfig* cfg, const char* iri)
{
	int err;
	err = get_directory_and_filename(dfff, cfg, iri);
	if(err != 0){
		return 1;
	}
	dfff->opendir = NULL;
	return 0;
}

static size_t find_first_segment_after_sub(const char* sub, const char* super){
	size_t i = 0;
	while(sub[i] == super[i] && sub[i] != '\0'){
		i++;
	}
	if(sub[i] == '\0' && sub[i-1] == '/'){//found directorypath
		return i;
	} else if (sub[i] == '\0' && super[i] == '/'){//found directorypath
		return i + 1;
	}
	return 0;
}

static const char* find_last_segment(const char* iri){
	const char* ret = iri;
	//if (iri == NULL) return NULL;
	for(const char* x=iri; x[0] != '\0'; x++){
		switch(*x){
			case '/':
				ret = x;
				break;
			case '?': //reached query
			case '#':
				return ret;
		}
	}
	return ret;
}


static int get_directory_and_filename(DataFindFeasibleFiles* dfff, CallbackConfig* cfg, const char* iri){
	int qq;
	size_t start_relative_segment;
	const char* filename_segment;
	char* directory_path;
	for(Path2IriList* x = cfg->path2iri_list; x != NULL; x = x->rest){
		start_relative_segment = find_first_segment_after_sub(x->first.iri, iri);
		if (start_relative_segment <= 0){
			continue;
		}
		if(iri[start_relative_segment] == '\0'){
			fprintf(stderr, "ERROR get_directory_and_filename not fully implemented\n");
			return 1;
		}
		filename_segment = find_last_segment(iri + start_relative_segment);
		dfff->directory_path = generate_directory_path(
				x->first.path, iri+start_relative_segment,
				filename_segment);
		dfff->filename = filename_segment;
		dfff->l_filename = strlen(dfff->filename);
		return 0;
	}
	return 1;
}


static char* generate_directory_path(const char* basepath, const char* addiri, const char* addiri_end)
{
	char *ret, *tmps;
	int tmpl = 0;
	size_t tmpi, l = 0;
	for(const char* tmp = basepath; *tmp!='\0'; tmp++){
		l++;
	}
	for(const char* tmp = addiri; tmp!=addiri_end; tmp++){
		l++;
		tmpl++;
		//TODO if windows check for \ and add 3 instead
	}
	tmps = malloc(tmpl+1);
	sprintf(tmps, "%.*s", tmpl, addiri);
	ret = malloc(l + 2);
	tmpi = cwk_path_join(basepath, tmps, ret, l+1);
	free(tmps);
	return ret;
}


static NextFeasibleFile DataFindFeasibleFiles_next(DataFindFeasibleFiles* x){
	size_t namelen;
	size_t _extlength;
	const char* fileext;
	NextFeasibleFile ret = {.err = 0};
	if(x->opendir == NULL){
		x->opendir = opendir(x->directory_path);
		if(x->opendir == NULL){
			return NO_NEXT_FILE;
		}
	}
	for (struct dirent* dp = readdir(x->opendir);
			dp != NULL;
			dp = readdir(x->opendir))
	{
		switch(dp->d_type){
			case DT_REG:
				break;
			default:
				continue;
		}
		namelen = strlen(dp->d_name);
		if (namelen < x->l_filename){
			continue;
		}
		if (0 != memcmp(x->filename, dp->d_name, x->l_filename)){
			continue;
		}
		if (namelen == x->l_filename){
			//ignore missing extension
			if (!cwk_path_get_extension(dp->d_name, &fileext,
							&_extlength))
			{
				fileext = "";
			}
		} else {
			//Expect to find extension of file
			if (!cwk_path_get_extension(dp->d_name, &fileext,
							&_extlength))
			{
				continue;
			}
			//File extension must located at end of basefilename
			if (fileext != dp->d_name + x->l_filename){
				continue;
			}
		}
		ret.filepath = my_join_path(x->directory_path, dp->d_name);
		if(ret.filepath != NULL){
			ret.err = 0;
		} else {
			fprintf(stderr, "INTERNAL ERROR DataFindFeasibleFiles_next\n");
			ret.err = 1;
		}
		ret.ext = fileext + 1;
		return ret;
	}
	return NO_NEXT_FILE;
}

static void release_NextFeasibleFile(NextFeasibleFile x){
	if(x.filepath != NULL){
		free(x.filepath);
	}
}

static char* my_join_path(const char* first, const char* second){
	char* ret;
	size_t lfirst, lsecond, lbuffer, tmpi;
	lfirst = strlen(first);
	lsecond = strlen(second);
	lbuffer = lfirst + lsecond + 3;
	ret = malloc(lbuffer + 3);
	if (ret == NULL){
		return NULL;
	}
	tmpi = cwk_path_join(first, second, ret, lbuffer);
	return ret;
}

static char* load_into_memory(const char* filepath){
        char *ret;
        long fsize;
        FILE *f = fopen(filepath, "rb");
        if (f == NULL) return NULL;
        fseek(f, 0, SEEK_END);
        fsize = ftell(f);
        rewind(f);
        //fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

        ret = malloc(fsize + 1);
        fread(ret, fsize, 1, f);
        ret[fsize] = 0;
        fclose(f);
        return ret;
}


void release_DataDescription(DataDescription x){
	if(x.data != NULL){
		free(x.data);
	}
	if(x.format != NULL){
		free(x.format);
	}
}
