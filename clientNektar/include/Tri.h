#ifndef TRI_H
#define TRI_H

class Tri: public Element{
private:
public:
  // Constructors
  Tri();                                             // default constructor
  Tri(Element *);                                    // constructor
  Tri(int i_d, char ty, int *qsize, int *jsize, Coord *X);
  Tri(int i_d, char ty, int L, int Qa, int Qb, int Qc, Coord *X);

  // Memory routines
  void Mem_J(int *list, char trip);
  void Mem_Q();

  void Mem_shift(double *, double *, char);  // updates storage pters
  void Mem_free();                           // frees existing storage

  // Operators
  Tri& operator=(Tri&);                              // assignement operator
  Tri& operator*=(Tri&);                             // mulitplying operator
  Tri& operator*=(double&);                          // mulitplying operator
  Tri& operator+=(Tri&);                             // addition operator

  // Local Matrix builders
  void MassMat (LocMat *);                           // return mass-matri(ces)
  void MassMatC(LocMat *);
  void HelmMatC(LocMat *, Metric *lambda);           // return Helmholtz op.
  void PSE_Mat(Element *E, Metric *lambda, LocMat *pse, double *DU);
  void PSE_Mat(Element *E, LocMat *pse, double *DU);
  void BET_Mat(Element *P, LocMatDiv *bet, double *beta, double *sigma);
  void LapMat  (LocMat *);                           // return Laplacian op.
  void mat_free(LocMat *m);
  LocMat *mat_mem();
  void fill_diag_massmat();              // fill modes with mass diagonal
  void fill_diag_helmmat(Metric *lambda);          // fill modes with helm diagonal


  // Transforms and inner-products
  void   Jbwd(Element*, Basis*);
  void   Jbwdfac1(int face, double *vj, double *v);
  void   Jfwd(Element*);
  double iprod(Mode *x, Mode *y);
  double iprodlap(Mode *x, Mode *y, Mode *fac);

  void HelmHoltz(Metric *lambda);
  void form_diprod(double *u1, double *u2, double *u3, Mode *m);

  // orthogonal transform routines
  void Obwd  (double *, double *, int);
  void Ofwd  (double *, double *, int);
  void Ofwd  (double *, double *, int, int);
  void Add_Surface_Contrib(Element *, double *in, char dir);
  void Add_Surface_Contrib(Element *, double *in, char dir, int edge);
  void Add_Surface_Contrib(Element *, double *in, char dir, int edge, 
			   int invjac);
  void Add_Surface_Contrib(double *in, char dir, int edge);
  void Add_Surface_Contrib(double *in, char dir, int edge, int invjac);
  void fill_edges(double *ux, double *uy, double *uz);

  void SubtractBC(double alpha, double  beta, int Bface,  Element *out);

  // Global matrix routines
  void condense(LocMat *m, Bsystem *Ubsys, char pack);
  void project(LocMat *m, Bsystem *Ubsys);
  void LowEnergyModes(Bsystem *B, int *Ne, int *Nf, 
			 double ***Rv, double ***Rvi, double ***Re);
  void MakeLowEnergyModes(Bsystem *B, int *Ne, int *Nf, 
			  double ***Rv, double ***Rvi, double ***Re);

  // Bndry routines
  Bndry *gen_bndry(char bc, int face, ...);
  void  update_bndry(Bndry *Ubc, int save);
  void   MemBndry(Bndry *B, int face, int Je);
  void JtransEdge(Bndry *B, int id, int loc, double *f);
  void JtransFace(Bndry *, double *);

  void MakeFlux(Bndry *B, int iface, double *f);

  // Element Identifier
  Nek_Facet_Type identify(){ return Nek_Tri;}         // identify

  // Transformation routines
  void Trans(Element *, Nek_Trans_Type);              // Transform to Tri
  void Iprod(Element *);                              // Inner product to Tri
  void Iprod_d(Element *,Basis *, Basis *);           // Inner product to Tri
  void Sign_Change();

  // Derivatives routines
  void Grad (Element *, Element *, Element *, char Trip);
  void GradT(Element *, Element *, Element *, char Trip);
  void GradT(Element *, Element *, Element *, char Trip, bool invW);
  void Grad_d(double *, double *, double *, char Trip);  
  void Grad_h(double *, double *, double *, double *, char Trip); 
  void GradT_h(double *, double *, double *, double *, char Trip); 
  void GradT_h(double *, double *, double *, double *, char Trip, bool invW); 
  void getD(double ***da, double ***dat,double ***db,double ***dbt,
	    double ***dc, double ***dct);
                                                   // Get differential matrix

  void fillElmt(Mode *v);
  void fill_gradbase(Mode *gb, Mode *m, Mode *mb, Mode *fac);
  Basis *getbasis();
  Basis *derbasis();

  // Co-ordinate functions
  void set_curved(Curve*){;}                         // fix curve sides
  void coord(Coord *X);                              // get quadrature coords
  void fillvec(Mode *v, double *f);                  //
  void straight_elmt(Coord *X);                      //
  void curved_elmt(Coord *X);                        //
  void straight_edge(Coord *X, int edge);            // 
  void GetFaceCoord(int face, Coord *X);             //

  // Error functions
  void Set_field(char *string);                      // set field to function
  void Error(char *string);                          // compare with function
  double L2_error_elmt(char *string);
  double H1_error_elmt(char *string);
  void Verror(double *u, char *string);
  double Int_error( char *string);
  double Norm_li();
  double Norm_l2();
  void Norm_l2m(double *l2, double *area);
  double Norm_h1();
  void Norm_h1m(double *h1, double  *area);

  // Curved sides
  void set_curved_elmt(Element_List*);
  void genArc(Curve *cur, double *x, double *y);
  void genNaca4(Curve *cur, double *x, double *y);
  void genFile(Curve *cur, double *x, double *y);

  void CoordTransEdge(double *f, double *fhat, int edge);
  void get_mmat1d(double **mat, int L);
  
  // Geometric factors 
  void set_geofac();
  void free_geofac();

  void Surface_geofac(Bndry *B);
  void InterpToFace1(int from_face, double *f, double *fi);
  void InterpToGaussFace(int from_face, double *f, 
				 int qaf, int qbf, double *fi);

  void set_solve(int fac, int mask);
  void Add_flux_terms(Bndry *Ebc);
  void setbcs(Bndry *Ubc, double *bc);
  void GetFace(double*, int, double *);

  void dump_mesh(FILE*);  
    
  int  Nfmodes();
  int  vnum(int,int);
  int  fnum(int,int);
  int  fnum1(int,int);
  int  ednum(int,int);
  int  ednum1(int,int);
  int  ednum2(int,int);

  int dim(){return 2;}
  int Nfverts(int);

  void fill_column(double **Mat, int loc, Bsystem *B, int nm, int offset);
  void WeakDiff(Mode *m, double *ux, double *uy,double *uz, int con);

  int  data_len(int *size);
  void Copy_field(double *, int *); 

  void close_split(Element_List *EL, Bndry **Ubc, int nfields, int *&flag);
  void split_element(Element_List *EL, Bndry **Ubc, int nfields, int *&flag);
  void split_edge(int edg, Element_List *EL, Bndry **Ubc, int nfields,int *flag);
  
  void delete_element(Element_List *EL, Bndry **, int, int *flag);
  void set_edge_geofac();
  void set_edge_geofac(int invjac);
  void PutFace(double*, int);

  void GetZW(double **za, double **wa, double **zb, double **wb, double **zc, double **wc);

  int edvnum(int,int);

  void       DivMat  (LocMatDiv *, Element *P);    // return Divergence op.
  LocMatDiv *divmat_mem(Element *P);
  void       divmat_free(LocMatDiv *m);
  double     get_1diag_massmat(int id);  /* get diagional component of 
		  			mass matrix corres. to id */
  void       condense_stokes(LocMat *m, LocMatDiv *d, Bsystem *Ubsys, 
			     Bsystem *Pbsys, Element *P);
  void       project_stokes(Bsystem *Pbsys, int asize, int geom_id);

  // Particle routines
  int        intersect_bnd    (Coord *Xi, double *vp, 
			       double *dt_remain, int *face);
  int        lcoords2face    (Coord *Xi, int *fac);
  void       face2lcoords    (Coord *Xi, int *fac);
  void       Cart_to_coll    (Coord csi, Coord *A);
  void       Coll_to_cart    (Coord A, Coord *csi);
};

#endif
