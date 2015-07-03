/*
 * pid.hpp
 *
 *  Created on: Jul 3, 2015
 *      Author: rwlodarz
 */

#ifndef INCLUDE_PID_HPP_
#define INCLUDE_PID_HPP_

#include <vector>

struct PidConfiguration
{
    float p;
    float i;
    float d;
    float epsilon;
    float miniumim;
    float maximum;
};

class Pid
{
public:
    Pid(PidConfiguration& p_pidConfiguration, float p_samplingTime);
    ~Pid();
    
    void computeOutput();

    void setConfiguration(const PidConfiguration& p_configuration) { m_configuration = p_configuration; }
    void setProcessVariable(float p_processVariable);
    void setSamplingTime(float p_samplingTime) { m_samplingTime = p_samplingTime; }
    void setSetPoint(float p_setPoint) { m_setPoint = p_setPoint; }

    const PidConfiguration& getPidConfiguration() const { return m_configuration; }
    float getOutput() const { return m_output; }
private:
    inline void compute();

    float m_setPoint;
    float m_samplingTime;
    float m_output;
    float m_i;
    std::vector<float> m_processVariable;
    std::vector<float> m_error;
    PidConfiguration m_configuration;
};



#endif /* INCLUDE_PID_HPP_ */
