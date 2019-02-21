#include "parameterinterface.h"

ParameterInterface::ParameterInterface()
{

}

ParameterInterface::~ParameterInterface()
{

}

// #################### Public #####################
void ParameterInterface::addAnalogueSensor(AnalogueSensorMenu *sensor)
{
    a_sensors.append(sensor);
}

void ParameterInterface::addDigitalSensor(DigitalSensorMenu *sensor)
{
    d_sensors.append(sensor);
}

void ParameterInterface::addPump(PumpMenu *pump)
{
    pumps.append(pump);
}

QList<aParams> ParameterInterface::getAnalogueSensorParams()
{
    QList<aParams> params;
    for (AnalogueSensorMenu *menu : a_sensors) {
        params.append(menu->getParams());
    }
    return params;
}

QList<dParams> ParameterInterface::getDigitalSensorParams()
{
    QList<dParams> params;
    for (DigitalSensorMenu *menu : d_sensors) {
        params.append(menu->getParams());
    }
    return params;
}

QList<pParams> ParameterInterface::getPumpParams()
{
    QList<pParams> params;
    for (PumpMenu *menu : pumps) {
        params.append(menu->getParams());
    }
    return params;
}
// #################### Private ####################
