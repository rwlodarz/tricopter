/*
 * pid.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: rwlodarz
 */

#include "include/pid.hpp"

#include <algorithm>

Pid::Pid(PidConfiguration& p_pidConfiguration, float p_samplingTime) :
            m_configuration(p_pidConfiguration),
            m_samplingTime(p_samplingTime),
            m_output(0.0),
            m_processVariable{0.0, 0.0, 0.0},
            m_setPoint(0.0),
            m_i(0.0),
            m_error{0.0, 0.0, 0.0}
{

}

void Pid::computeOutput()
{
    m_i = 0;

    m_error[2] = m_error[1];
    m_error[1] = m_error[0];
    m_error[0] = m_samplingTime - m_processVariable;

    if(std::abs(m_error[0] < m_configuration.epsilon))
        m_i = m_configuration.i * m_samplingTime * m_error[0];

    if(m_configuration.epsilon > 0)
    {
        compute();
    }
    else
    {
         if(m_error[0] < -10)
              m_output = m_configuration.miniumim;
         else if(m_error[0] > 10)
              m_output = m_configuration.maximum;
    }

    m_output = std::max(std::min(m_output,m_configuration.maximum),m_configuration.miniumim); //TODO: WTF?!
}

void Pid::setProcessVariable(float p_processVariable)
{
    m_processVariable[2] = m_processVariable[1];
    m_processVariable[1] = m_processVariable[0];
    m_processVariable[0] = p_processVariable;
}
void Pid::compute()
{
    m_output = m_output - m_configuration.p*(m_processVariable[0] - m_processVariable[1]) + m_i - m_configuration.d*(m_processVariable[0] - 2*m_processVariable[1] + m_processVariable[2]) / m_samplingTime;
}



