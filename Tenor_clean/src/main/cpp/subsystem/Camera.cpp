#include "subsystem/Camera.h"

Camera::Camera(){};

// This method will be called once per scheduler run

double Camera::GetPitch(int Id_1, int Id_2)
{
    std::cout << m_camera.GetCameraName() << std::endl;
    if (m_camera.HasTargets())
    {
        photon::PhotonPipelineResult result = m_camera.GetLatestResult();
        std::span<const photon::PhotonTrackedTarget> targetsList = result.GetTargets();
        std::vector<photon::PhotonTrackedTarget>::iterator it;
        photon::PhotonTrackedTarget target;

        for (int i = 0; i < result.targets.size(); i++)
        {
            target = result.targets[i];

            if (target.GetFiducialId() == Id_1 || target.GetFiducialId() == Id_2)
            {
                m_verticalRollingAverage.add(target.GetPitch());
                std::cout << target.GetFiducialId() << std::endl;
            }
        }
    }
    else
    {
        m_verticalRollingAverage.add(m_verticalRollingAverage.get());
    }
    return m_verticalRollingAverage.get();
}

void Camera::Periodic()
{
}