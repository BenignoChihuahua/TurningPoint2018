/* states */
#define states 8

/* observables */
#define obs 4

typedef struct {

    int n;           /* number of state values */
    int m;           /* number of observables */

    double x[states];     /* state vector */

    double P[states][states];  /* prediction error covariance */
    double Q[states][states];  /* process noise covariance */
    double R[obs][obs];  /* measurement error covariance */

    double G[states][obs];  /* Kalman gain; a.k.a. K */

    double F[states][states];  /* Jacobian of process model */
    double H[obs][states];  /* Jacobian of measurement model */

    double Ht[states][obs]; /* transpose of measurement Jacobian */
    double Ft[states][states]; /* transpose of process Jacobian */
    double Pp[states][states]; /* P, post-prediction, pre-update */

    double fx[states];   /* output of user defined f() state-transition function */
    double hx[obs];   /* output of user defined h() measurement function */

    /* temporary storage */
    double tmp0[states][states];
    double tmp1[states][obs];
    double tmp2[obs][states];
    double tmp3[obs][obs];
    double tmp4[obs][obs];
    double tmp5[obs];

} ekf_t;
