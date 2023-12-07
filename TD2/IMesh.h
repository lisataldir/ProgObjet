#ifndef IMESH_H_
#define IMESH_H_

class IMesh{
public :
    virtual double getInitialTime() const;
    virtual double getFinalTime() const;
    virtual double getStepTime() const;
    virtual double getInitialSpace() const;
    virtual double getFinalSpace() const;
    virtual double getStepSpace() const;

    virtual int x_size() const;
    virtual double x_i(int i);


    //Add mu, sigma and a
    virtual double getMu() const;
    virtual double getSigma() const;
    virtual double getA() const;

    virtual ~IMesh() = default;

};

class UniformMesh : public IMesh{
private :
    double t_init = 0;
    double t_final = 2;
    double dt = 0.1;
    double x_min = 0;
    double x_max = 10;
    double dx = 0.1;

    double mu = (x_max - x_min)/2;
    double sigma = 10*dx;
    double a = 0.5*dx/dt;

public :
    //constructeur
    UniformMesh(double t_init, double t_final, double dt, double x_min, double x_max, double dx);

    double getInitialTime() const override;
    double getFinalTime() const override;
    double getStepTime() const override;
    double getInitialSpace() const override;
    double getFinalSpace() const override;
    double getStepSpace() const override;

    int x_size() const override;
    double x_i(int i) override;

    double getMu() const override;
    double getSigma() const override;
    double getA() const override;

};

#endif