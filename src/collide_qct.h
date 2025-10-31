/* ----------------------------------------------------------------------
   CollideQCT - independent copy of collide_vss header

   This header declares CollideQCT (registered as style "qct").
   The implementation in collide_qct.cpp provides an independent
   copy of the VSS behavior so you can modify QCT/ANT internals
   without touching collide_vss.* files.
------------------------------------------------------------------------- */

#ifdef COLLIDE_CLASS

CollideStyle(qct,CollideQCT)

#else

#ifndef SPARTA_COLLIDE_QCT_H
#define SPARTA_COLLIDE_QCT_H

#include "collide.h"
#include "particle.h"

namespace SPARTA_NS {

class CollideQCT : public Collide {
 public:
  CollideQCT(class SPARTA *, int, char **);
  virtual ~CollideQCT();
  virtual void init();

  double vremax_init(int, int);
  virtual double attempt_collision(int, int, double);
  double attempt_collision(int, int, int, double);
  virtual int test_collision(int, int, int, Particle::OnePart *,
                             Particle::OnePart *);
  virtual void setup_collision(Particle::OnePart *, Particle::OnePart *);
  virtual int perform_collision(Particle::OnePart *&, Particle::OnePart *&,
                                Particle::OnePart *&);
  double extract(int, int, const char *);

  struct State {      // two-particle state
    double vr2;
    double vr;
    double imass,jmass;
    double ave_rotdof;
    double ave_vibdof;
    double ave_dof;
    double etrans;
    double erot;
    double evib;
    double eexchange;
    double eint;
    double etotal;
    double ucmf;
    double vcmf;
    double wcmf;
  };

  struct Params {             // VSS model parameters (copied for QCT use)
    double diam;
    double omega;
    double tref;
    double alpha;
    double rotc1;
    double rotc2;
    double rotc3;
    double vibc1;
    double vibc2;
    double mr;
  };

 protected:
  int relaxflag,eng_exchange;
  double vr_indice;
  double **prefactor; // static portion of collision attempt frequency
  struct State precoln;       // state before collision
  struct State postcoln;      // state after collision

  Params **params;             // params for each species
  int nparams;                // # of per-species params read in

  void SCATTER_TwoBodyScattering(Particle::OnePart *,
                                 Particle::OnePart *);
  void EEXCHANGE_NonReactingEDisposal(Particle::OnePart *,
                                      Particle::OnePart *);
  void SCATTER_ThreeBodyScattering(Particle::OnePart *,
                                   Particle::OnePart *,
                                   Particle::OnePart *);
  void EEXCHANGE_ReactingEDisposal(Particle::OnePart *,
                                   Particle::OnePart *,
                                   Particle::OnePart *);

  double sample_bl(RanKnuth *, double, double);
  double rotrel (int, double);
  double vibrel (int, double);

  void read_param_file(char *);
  int wordparse(int, char *, char **);
};

} /* namespace SPARTA_NS */

#endif /* SPARTA_COLLIDE_QCT_H */

#endif /* COLLIDE_CLASS */

/* ERROR/WARNING messages:

E: Illegal ... command

Self-explanatory.  Check the input script syntax and compare to the
documentation for the command.  You can use -echo screen as a
command-line option when running SPARTA to see the offending line.

E: Species %s did not appear in VSS parameter file

Self-explanatory.

E: VSS parameters do not match current species

Species cannot be added after VSS colision file is read.

E: Cannot open VSS parameter file %s

Self-explanatory.

E: Incorrect line format in VSS parameter file

Number of parameters in a line read from file is not valid.

E: Request for unknown parameter from collide

VSS model does not have the parameter being requested.

*/
