#include "../EKF/EKF.h"

#define states 3     // Three state values: x position, y position, and heading
#define    obs 2     // Two measurements: wheel odometry, gyro sensor, and in the future(accelerometer)

class RobotPose : public EKF {

    public:

        RobotPose()
        {
            // We approximate the process noise using a small constant
            this->setQ(0, 0, .0001);
            this->setQ(1, 1, .0001);

            // Same for measurement noise
            this->setR(0, 0, .0001);
            this->setR(1, 1, .0001);
            this->setR(2, 2, .0001);
        }

    protected:

        void model(double fx[states], double F[states][states], double hx[obs], double H[obs][states])
        {
            // Process model is f(x) = x
            fx[0] = this->x[0];
            fx[1] = this->x[1];

            // So process model Jacobian is identity matrix
            F[0][0] = 1;
            F[1][1] = 1;

            // Measurement function simplifies the relationship between state and sensor readings for convenience.
            // A more realistic measurement function would distinguish between state value and measured value; e.g.:
            //   hx[0] = pow(this->x[0], 1.03);
            //   hx[1] = 1.005 * this->x[1];
            //   hx[2] = .9987 * this->x[1] + .001;
            hx[0] = this->x[0]; // Barometric pressure from previous state
            hx[1] = this->x[1]; // Baro temperature from previous state
            hx[2] = this->x[1]; // LM35 temperature from previous state

            // Jacobian of measurement function
            H[0][0] = 1;        // Barometric pressure from previous state
            H[1][1] = 1 ;       // Baro temperature from previous state
            H[2][1] = 1 ;       // LM35 temperature from previous state
        }
};

RobotPose ekf;
//SFE_BMP180 baro;

void setup() {

  /*
    Serial.begin(9600);

    // Start reading from baro
    baro.begin();

    // Set up to read from LM35
    analogReference(INTERNAL);
   */
}


void OnLoop() {

    // Read pressure, temperature from BMP180
    //double baroTemperature, baroPressure;
    //getBaroReadings(baroTemperature, baroPressure);

    //read wheel odometry from optical encoders

    // Read temperature from LM35
    //float lm35Temperature = analogRead(LM35_PIN) / 9.31;

    //read angle from gyro

    // Send these measurements to the EKF
    double z[3] = {baroPressure, baroTemperature, lm35Temperature};
    ekf.step(z);

    //send the odometry information and gyro angle to the EKF

    // Report measured and predicte/fused values
    /*
    Serial.print(z[0]);
    Serial.print(" ");
    Serial.print(z[1]);
    Serial.print(" ");
    Serial.print(z[2]);
    Serial.print(" ");
    Serial.print(ekf.getX(0));
    Serial.print(" ");
    Serial.println(ekf.getX(1));
    */
    //print out the observation values and predicted/fused values
}


// Adapted from https://github.com/sparkfun/BMP180_Breakout

/*void getBaroReadings(double & T, double & P)
{
    char status = baro.startTemperature();

    if (status != 0) {
        //delay(status);
        status = baro.getTemperature(T);
        if (status != 0) {
            status = baro.startPressure(3);
            if (status != 0) {
                //delay(status);
                status = baro.getPressure(P,T);
                if (status == 0)
                    printf("error retrieving pressure measurement \n");
            }
            else printf("error starting pressure measurement \n");
        }
        else printf("error retrieving temperature measurement \n");
    }
    else printf("error starting temperature measurement \n");
}*/
