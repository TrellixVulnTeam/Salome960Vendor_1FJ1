/* -*- mode:C; coding:utf-8 -*- */
/*  This file is part of MED.
 *
 *  COPYRIGHT (C) 1999 - 2020  EDF R&D, CEA/DEN
 *  MED is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  MED is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with MED.  If not, see <http://www.gnu.org/licenses/>.
 */

# ifndef __UTILITES_H__
# define __UTILITES_H__

#include <stdlib.h>
#include <med_exit_if.h>

/* pour indiquer le statut des arguments des fonctions. */

#ifdef _IN
#error _IN already defined
#endif
#define _IN

#ifdef _OUT
#error _OUT already defined
#endif
#define _OUT

#ifdef _INOUT
#error _INOUT already defined
#endif
#define _INOUT

#ifdef _UNUSED
#error _UNUSED already defined
#endif
#define _UNUSED







/* --- Pour afficher le nom du fichier source courant et le numero de la ligne courante --- */
/* --- sur la stderr.                                                                   --- */

# define ICI			{\
					fflush(stdout);\
					fprintf(stderr, "%s [%d] : " , __FILE__ , __LINE__ ) ;\
					fflush(stderr) ;\
				}







/* --- Pour afficher la date et l'heure de la compilation du fichier source courant,    --- */
/* --- sur la stdout.                                                                   --- */

# ifdef INFOS_COMPILATION
# error INFOS_COMPILATION already defined
# endif
# define INFOS_COMPILATION	{\
					fflush(stderr);\
					fprintf(stdout, "%s [%d] : " , __FILE__ , __LINE__ ) ;\
					fprintf(stdout,"Compilation le %s" , __DATE__);\
					fprintf(stdout," a %s" , __TIME__ );\
					fprintf(stdout,"\n\n\n" );\
					fflush(stdout) ;\
				}







/* --- Pour attendre "secondes" secondes et afficher un message sur la stderr indiquant --- */
/* --- cette attente volontaire.                                                        --- */

# ifdef ATTENTE
# error ATTENTE already defined
# endif
# define ATTENTE(secondes)	{\
					ICI ;\
					fprintf( stderr, "ATTENTE de %d secondes" , secondes);\
					fflush(stderr) ;\
					sleep(secondes) ;\
					fprintf( stderr, "\n" );\
					fflush(stderr) ;\
				}







/* ----------    Les macros suivantes ne doivent pas deja exister !              ---------- */

# ifdef EXECUTION
# error EXECUTION already defined
# endif
# ifdef INTERRUPTION
# error INTERRUPTION already defined
# endif
# ifdef ISCRUTE
# error ISCRUTE already defined
# endif
# ifdef RSCRUTE
# error RSCRUTE already defined
# endif
# ifdef SSCRUTE
# error SSCRUTE already defined
# endif
# ifdef CSCRUTE
# error CSCRUTE already defined
# endif
# ifdef XSCRUTE
# error XSCRUTE already defined
# endif
# ifdef MESSAGE
# error MESSAGE already defined
# endif



/* D�finition du format � utiliser pour afficher un med_int */
# define IFORMAT_int "%d"
# define IFORMAT_long "%ld"
# define IFORMAT_llong "%lld"
# define IFORMAT IFORMAT_long

#if ! defined(MESGERR)
#error "Explicit error messages must be either activated or deactivated, hence MESGERR macro must be defined."
#error "Verify that you include med_utils.h after med_config.h, thanks."
#endif

# if MESGERR == 1 || defined(MED_MESGERR_FOR_TOOLS)


/* --- Pour tracer sur la stderr l'execution d"une instruction.                         --- */

# define EXECUTION(instruction)	{\
					ICI ;\
					fprintf( stderr,"INSTRUCTION %s" , #instruction ) ;\
					fflush(stderr);\
					instruction ;\
					fflush(stdout);\
					fprintf( stderr," FRANCHIE\n" ) ;\
					fflush(stderr);\
				}







/* --- Pour afficher un message d'interruption volontaire et retourner le code retour   --- */
/* --- "code"                                                                           --- */

# define INTERRUPTION(code)	{\
					ICI ;\
					fprintf( stderr," INTERRUPTION code = %d",code) ;\
					fprintf(stderr,"\n") ;\
					exit(code) ;\
				}







/* --- Pour conditionner la poursuite du traitement par la validite de la condition     --- */
/* --- "condition".                                                                     --- */

# ifndef ASSERT
# define ASSERT(condition)	if( !(condition) ){\
					ICI ;\
					fprintf(stderr,"condition %s VIOLEE\n",#condition);\
					INTERRUPTION(17);\
				}
# endif		/* # ifndef ASSERT */


/* --- Pour conditionner la poursuite du traitement au fait qu'une chaine ne finie pas par un blanc --- */
/* --- "nofinalblank".                                                                              --- */
# ifndef NOFINALBLANK
# define NOFINALBLANK(chaine,label) if( ( chaine[strlen(chaine)-1] == ' ' ) ){ \
					ICI ;\
					fprintf(stderr,"La chaine |%s| ne doit pas finir par un caract�re blanc.\n",chaine);\
					goto label;			\
				}
# endif		/* # ifndef NOFINALBLANK */






/* --- Pour afficher sur la stderr la valeur d'une variable precedee de son nom.        --- */

# define ISCRUTE(entier)	ISCRUTE_long(entier)

# define ISCRUTE_int(entier)	{\
					ICI ;\
					fprintf(stderr,"%s = %d\n",#entier,entier) ;\
					fflush(stderr) ;\
				}
# define ISCRUTE_long(entier)	{\
					ICI ;\
					fprintf(stderr,"%s = %ld\n",#entier,entier) ;\
					fflush(stderr) ;\
				}
# define ISCRUTE_llong(entier)	{\
					ICI ;\
					fprintf(stderr,"%s = %lld\n",#entier,entier) ;\
					fflush(stderr) ;\
				}
# define ISCRUTE_size(entier)	{\
					ICI ;\
					fprintf(stderr,"%s = %llu\n",#entier,entier) ;\
					fflush(stderr) ;\
				}
# define ISCRUTE_id(entier) ISCRUTE_long(entier)
# define RSCRUTE(reel)		{\
					ICI ;\
					fprintf(stderr,"%s = %f\n",#reel,reel) ;\
					fflush(stderr) ;\
				}
# define XSCRUTE(pointeur)		{\
					ICI ;\
					fprintf(stderr,"%s = %x\n",#pointeur,pointeur) ;\
					fflush(stderr) ;\
				}
# define CSCRUTE(car)		{\
					ICI ;\
					fprintf(stderr,"%s = %c\n",#car,car) ;\
					fflush(stderr) ;\
				}
# define SSCRUTE(chaine)	{\
					ICI ;\
					fprintf(stderr,"%s = \"%s\"\n",#chaine,chaine) ;\
					fflush(stderr) ;\
				}
# define MESSAGE(chaine)	{\
					ICI ;\
					fprintf(stderr,"%s\n",chaine) ;\
					fflush(stderr) ;\
				}
# define FIN(nom)		{\
					ICI ;\
					fprintf( stderr , "} FIN %s\n\n\n" , nom ) ;\
					fflush(stderr) ;\
				}
# define DEBUT(nom)		{\
					fprintf( stderr , "\n\n\n") ;\
					ICI ;\
					fprintf( stderr , "{ DEBUT %s\n" , nom ) ;\
					fflush(stderr) ;\
				}


# else		/* # if MESGERR */



# define EXECUTION(instruction) instruction
# define INTERRUPTION(code)

# ifndef ASSERT
# define ASSERT(condition)
# endif

# define NOFINALBLANK(chaine,label)

# define ISCRUTE(entier)
# define ISCRUTE_int(entier)
# define ISCRUTE_long(entier)
# define ISCRUTE_llong(entier)
# define ISCRUTE_size(entier)
# define ISCRUTE_id(entier)
# define RSCRUTE(reel)
# define CSCRUTE(car)
# define SSCRUTE(chaine)
# define MESSAGE(chaine)
# define DEBUT(nom)
# define FIN(nom)

# endif		/* # if MESGERR */

# ifdef WITH_EXCEPTIONS
#   ifdef __cplusplus
#    define EXIT_IF(expression,message,arg) {\
           if (expression != 0)						\
	     throw MEDerreur(__FILE__,__LINE__,message,arg); }
#   else
#     error Impossible d'activer l'option WITH_EXCEPTIONS avec un compilateur C
#   endif
# else
# define EXIT_IF(expression,message,arg) { exit_if(__FILE__,__LINE__,expression,message,arg); }
# endif


# endif		/* # ifndef __UTILITES_H__ */
