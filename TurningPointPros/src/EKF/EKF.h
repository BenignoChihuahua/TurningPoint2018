
#include <stdio.h>
#include <stdlib.h>
#include "EKFConfig.h"

// Support both Arduino and command-line versions
#ifndef MAIN
extern "C" {
#endif
    void ekf_init(void *, int, int);
    int ekf_step(void *, double *);
#ifndef MAIN
}
#endif

/**
 * A header-only class for the Extended Kalman Filter.  Your implementing class should #define the constant N and
 * and then #include <EKF.h>  You will also need to implement a model() method for your application.
 */
class EKF {

    private:

        ekf_t ekf;

    protected:

        /**
          * The current state.
          */
        double * x;

        /**
         * Initializes a EKF object.
         */
        EKF() {
            ekf_init(&this->ekf, states, obs);
            this->x = this->ekf.x;
        }

        /**
         * Deallocates memory for aEKF object.
         */
        ~EKF() { }

        /**
         * Implement this function for your EKF model.
         * @param fx gets output of state-transition function <i>f(x<sub>0 .. n-1</sub>)</i>
         * @param F gets <i>n &times; n</i> Jacobian of <i>f(x)</i>
         * @param hx gets output of observation function <i>h(x<sub>0 .. n-1</sub>)</i>
         * @param H gets <i>m &times; n</i> Jacobian of <i>h(x)</i>
         */
        virtual void model(double fx[states], double F[states][states], double hx[obs], double H[obs][states]) = 0;

        /**
         * Sets the specified value of the prediction error covariance. <i>P<sub>i,j</sub> = value</i>
         * @param i row index
         * @param j column index
         * @param value value to set
         */
        void setP(int i, int j, double value)
        {
            this->ekf.P[i][j] = value;
        }

        /**
         * Sets the specified value of the process noise covariance. <i>Q<sub>i,j</sub> = value</i>
         * @param i row index
         * @param j column index
         * @param value value to set
         */
        void setQ(int i, int j, double value)
        {
            this->ekf.Q[i][j] = value;
        }

        /**
         * Sets the specified value of the observation noise covariance. <i>R<sub>i,j</sub> = value</i>
         * @param i row index
         * @param j column index
         * @param value value to set
         */
        void setR(int i, int j, double value)
        {
            this->ekf.R[i][j] = value;
        }

    public:

        /**
         * Returns the state element at a given index.
         * @param i the index (at least 0 and less than <i>n</i>
         * @return state value at index
         */
        double getX(int i)
        {
            return this->ekf.x[i];
        }

        /**
         * Sets the state element at a given index.
         * @param i the index (at least 0 and less than <i>n</i>
         * @param value value to set
         */
        void setX(int i, double value)
        {
            this->ekf.x[i] = value;
        }

        /**
          Performs one step of the prediction and update.
         * @param z observation vector, length <i>m</i>
         * @return true on success, false on failure caused by non-positive-definite matrix.
         */
        bool step(double * z)
        {
            this->model(this->ekf.fx, this->ekf.F, this->ekf.hx, this->ekf.H);

            return ekf_step(&this->ekf, z) ? false : true;
        }
};
