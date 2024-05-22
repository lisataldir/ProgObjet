#ifndef IMESH_H_
#define IMESH_H_

class IMesh{
public:
    virtual double getInitialTime() const;
    virtual double getFinalTime() const;
    virtual double getStepTime() const;
    virtual double getInitialSpace() const;
    virtual double getFinalSpace() const;
    virtual double getStepSpace() const;
    virtual int x_size() const;
    virtual double x_i(int i);
    virtual ~IMesh() = default;
};

class UniformMesh : public IMesh{
private:
    double t_init;
    double t_final;
    double dt;
    double x_min;
    double x_max;
    double dx;
public:
    UniformMesh();
    UniformMesh(double InitialTime, double FinalTime, double StepTime, double InitialSpace, double FinalSpace, double StepSpace);

    double getInitialTime() const override;
    double getFinalTime() const override;
    double getStepTime() const override;
    double getInitialSpace() const override;
    double getFinalSpace() const override;
    double getStepSpace() const override;
    int x_size() const override;
    double x_i(int i) override;
};

class NonUniformMesh : public IMesh{
public:
    double getInitialTime() const override;
    double getFinalTime() const override;
    double getStepTime() const override;
    double getInitialSpace() const override;
    double getFinalSpace() const override;
    double getStepSpace() const override;
    int x_size() const override;
    double x_i(int i) override;
};

#endif