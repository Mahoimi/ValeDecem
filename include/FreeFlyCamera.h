#ifndef FREEFLYCAMERA_H
#define FREEFLYCAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

/*!
* \class FreeFlyCamera
* A camera unaffected by gravity which can move freely in the 3D scene
*/
class FreeFlyCamera {
    private:

        // The position of the camera in the scene
        glm::vec3 m_Position;

        float m_fPhi;
        float m_fTheta;
        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

    public:
        FreeFlyCamera(){
            m_Position = glm::vec3(0,0,5);
            m_fPhi = glm::degrees(M_PI);
            m_fTheta = 0;
            computeDirectionVectors();
        }

        explicit FreeFlyCamera(glm::vec3 position){
            m_Position = position;
            m_fPhi = glm::degrees(M_PI);
            m_fTheta = 0;
            computeDirectionVectors();
        }

        inline void moveLeft(float t){
            m_Position += t*m_LeftVector;
        }

        inline void moveFront(float t){
            m_Position += t*m_FrontVector;
        }

        inline void moveUp(float t){
            m_Position += t*m_UpVector;
        }

        inline void rotatePhi(float degrees){
            m_fPhi += degrees;
        }

        inline void rotateTheta(float degrees){
            m_fTheta += degrees;
            if((m_fTheta>glm::degrees(M_PI/2))||(m_fTheta<glm::degrees(-M_PI/2))){
                m_fTheta -= degrees;
            }
        }

        // Return the view matrix 4x4 of the camera
        inline glm::mat4 getViewMatrix() const{
            return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
        }

        // Return the position in the 3D scene of the camera
        inline glm::vec3& getPosition(){
			return m_Position;
        }

        // Return angle phi
        inline float& getPhi(){
            return m_fPhi;
        }

        // Return angle theta
        inline float& getTheta(){
            return m_fTheta;
        }

        // Set the position in the 3D scene of the camera
        inline void setPosition(glm::vec3 newPosition){
            m_Position = newPosition;
        }

        // Set angle phi
        inline void setPhi(float newPhi){
            m_fPhi = newPhi;
        }

        // Set angle theta
        inline void setTheta(float newTheta){
            m_fTheta = newTheta;
        }


        // Compute all the parameters and angles to get the spherical coordinates of the camera
        void computeDirectionVectors(){
            m_LeftVector = glm::vec3(
                                sin(glm::radians(m_fPhi)+(M_PI/2)),
                                0,
                                cos(glm::radians(m_fPhi)+(M_PI/2))
                            );

            m_FrontVector = glm::vec3(
                cos(glm::radians(m_fTheta))*sin(glm::radians(m_fPhi)),
                sin(glm::radians(m_fTheta)),
                cos(glm::radians(m_fTheta))*cos(glm::radians(m_fPhi))
            );
            m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
        }

        // Print all the infos of the Camera instance
        void toString() {
            std::cout << "Position : " << m_Position.x << "," << m_Position.y << "," << m_Position.z << std::endl;
            std::cout << "Phi : " << m_fPhi << std::endl;
            std::cout << "Theta : " << m_fTheta << std::endl;
            std::cout << "Front : " << m_FrontVector.x << "," << m_FrontVector.y << "," << m_FrontVector.z << std::endl;
            std::cout << "Left : " << m_LeftVector.x << "," << m_LeftVector.y << "," << m_LeftVector.z << std::endl;
            std::cout << "Up : " << m_UpVector.x << "," << m_UpVector.y << "," << m_UpVector.z << std::endl;
        }
};

#endif // FREEFLYCAMERA_H
