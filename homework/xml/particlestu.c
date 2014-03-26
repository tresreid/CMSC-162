
struct particles {
  struct quark;
  struct lepton;
  struct boson;
};

struct quark {
  int types;
  char *name;
  int mass;
  int charge;
  char *symbol;
};
struct lepton {
  int types;
  char *name;
  int mass;
  int charge;
  char *symbol;
};
struct boson {
  char *name;
  int mass;
  int charge;
  char *symbol;
  char *associated_force;
};
