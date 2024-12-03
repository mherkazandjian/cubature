typedef struct {
     unsigned dim;
     double *data;	/* length 2*dim = center followed by half-widths */
     double vol;	/* cache volume = product of widths */
} hypercube;

double compute_vol(const hypercube *h);
hypercube make_hypercube(unsigned dim, const double *center, const double *halfwidth);
hypercube make_hypercube_range(unsigned dim, const double *xmin, const double *xmax);
void destroy_hypercube(hypercube *h);
