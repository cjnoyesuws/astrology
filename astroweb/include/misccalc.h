
/* structures */

typedef struct HEM {
           short east;
           short west;
           short south;
           short north;
           };

typedef struct GEN {
           short feminine;
           short masculine;
           };

typedef struct ELE {
           short fire;
           short water;
           short earth;
           short air;
           };

typedef struct QUAL {
           short cardinal;
           short fixed;
           short _mutable;
           };

typedef struct MDL {
           short angular;
           short succedent;
           short cadent;
           };

typedef struct FUNL {
           short individual;
           short temporal;
           short relative;
           short terminal;
           };

extern HEM   hemispheres, comp_hemispheres;
extern GEN   genders, comp_genders;
extern ELE   elements, comp_elements;
extern QUAL  qualities, comp_qualities;
extern MDL   modals, comp_modals;
extern FUNL  functionals, comp_functionals;
extern short  aspect_count[], comp_aspect_count[];
extern short    scout_planet, comp_scout_planet;
extern short  sign_count[], comp_sign_count[];
extern short  house_count[], comp_house_count[];
