#include <clips.h>
#include "shared_information.h"

static const char *templates[] = {
	"(deftemplate "FRAMETEMPLATE"\n"
		"	(slot "FRAMESLOTOBJECT")\n"
		"	(slot "FRAMESLOTSLOTKEY")\n"
		"	(slot "FRAMESLOTSLOTVALUE"))\n",

	"(deftemplate "ATOMTEMPLATE"\n"
		"	(slot "ATOMSLOTOP")\n"
		"	(multislot "ATOMSLOTARGS"))\n",

	"(deftemplate "SUBCLASSTEMPLATE"\n"
		"	(slot "SUBCLASSSLOTSUB")\n"
		"	(slot "SUBCLASSSLOTSUPER"))\n",

	"(deftemplate "MEMBERTEMPLATE"\n"
		"	(slot "MEMBERSLOTINSTANCE")\n"
		"	(slot "MEMBERSLOTCLASS"))\n",

	"(deftemplate "EQUALTEMPLATE"\n"
		"	(slot "EQUALSLOTLEFT")\n"
		"	(slot "EQUALSLOTRIGHT"))\n",

	"(deftemplate "ATOMLISTTEMPLATE" (multislot "ATOMLISTSLOTITEMS"))",

	NULL
};

static const char *baserules[] = {
	"(defrule transfer-superclasses\n"
		"	("SUBCLASSTEMPLATE" ("SUBCLASSSLOTSUB" ?cls) ("SUBCLASSSLOTSUPER" ?extracls))\n"
		"	("MEMBERTEMPLATE" ("MEMBERSLOTINSTANCE" ?x) ("MEMBERSLOTCLASS" ?cls))\n"
		"	=>\n"
		"	(assert ("MEMBERTEMPLATE" ("MEMBERSLOTINSTANCE" ?x) ("MEMBERSLOTCLASS" ?extracls)))\n"
		")",

	"(defrule rdfs-domain-entail\n"
		"	("FRAMETEMPLATE"\n"
		"		("FRAMESLOTOBJECT" ?pred)\n"
		"		("FRAMESLOTSLOTKEY" <http://www.w3.org/2000/01/rdf-schema#domain>)\n"
		"		("FRAMESLOTSLOTVALUE" ?cls))\n"
		"	("FRAMETEMPLATE"\n"
		"		("FRAMESLOTOBJECT" ?subj)\n"
		"		("FRAMESLOTSLOTKEY" ?pred))\n"
		"	=>\n"
		"	(assert ("MEMBERTEMPLATE" ("MEMBERSLOTINSTANCE" ?subj) ("MEMBERSLOTCLASS" ?cls)))\n"
		")",

	"(defrule rdfs-range-entail\n"
		"	("FRAMETEMPLATE"\n"
		"		("FRAMESLOTOBJECT" ?pred)\n"
		"		("FRAMESLOTSLOTKEY" <http://www.w3.org/2000/01/rdf-schema#range>)\n"
		"		("FRAMESLOTSLOTVALUE" ?cls))\n"
		"	("FRAMETEMPLATE"\n"
		"		("FRAMESLOTSLOTVALUE" ?obj)\n"
		"		("FRAMESLOTSLOTKEY" ?pred))\n"
		"	=>\n"
		"	(assert ("MEMBERTEMPLATE" ("MEMBERSLOTINSTANCE" ?obj) ("MEMBERSLOTCLASS" ?cls)))\n"
		")",

	"(defrule remove-unneeded-atomlists\n"
	"	(declare (salience 1000))\n"
	"	?list <- ("ATOMLISTTEMPLATE")\n"
	"	(not ("FRAMETEMPLATE" ("FRAMESLOTOBJECT" ?list)))\n"
	"	(not ("FRAMETEMPLATE" ("FRAMESLOTSLOTKEY" ?list)))\n"
	"	(not ("FRAMETEMPLATE" ("FRAMESLOTSLOTVALUE" ?list)))\n"
	"	(not ("ATOMTEMPLATE" ("ATOMSLOTOP" ?list)))\n"
	"	(not ("ATOMTEMPLATE" ("ATOMSLOTARGS" $? ?list $?)))\n"
	"	(not ("ATOMLISTTEMPLATE" ("ATOMLISTSLOTITEMS" $? ?list $?)))\n"
	"	(not ("EQUALTEMPLATE" ("EQUALSLOTLEFT" ?list)))\n"
	"	(not ("EQUALTEMPLATE" ("EQUALSLOTRIGHT" ?list)))\n"
	"	(not ("MEMBERTEMPLATE" ("MEMBERSLOTINSTANCE" ?list)))\n"
	"	(not ("MEMBERTEMPLATE" ("MEMBERSLOTCLASS" ?list)))\n"
	"	(not ("SUBCLASSTEMPLATE" ("SUBCLASSSLOTSUB" ?list)))\n"
	"	(not ("SUBCLASSTEMPLATE" ("SUBCLASSSLOTSUPER" ?list)))\n"
	"	=>\n"
	"	(retract ?list)\n"
	")",

	NULL
};


bool load_basic_templates(Environment *env) {
	for (const char **deftempl = templates; *deftempl != NULL; deftempl++){
		BuildError err = Build(env, *deftempl);
		switch (err) {
			case BE_PARSING_ERROR:
				//fprintf(stderr, "Critical Internal error. "
				//		"Failed loading basic "
				//		"templates. happened "
				//		"with: '%s'\n", *deftempl);
				return false;
				break;
			case BE_NO_ERROR:
				break;
		}
	}
	for (const char **defrule = baserules; *defrule != NULL; defrule++){
		BuildError err = Build(env, *defrule);
		switch (err) {
			case BE_PARSING_ERROR:
				//fprintf(stderr, "Critical Internal error. "
				//		"Failed loading basic "
				//		"templates. happened "
				//		"with: '%s'\n", *defrule);
				return false;
				break;
			case BE_NO_ERROR:
				break;
		}
	}
	return true;
}
