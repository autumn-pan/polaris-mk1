#ifndef VECTOR_H
#define VECTOR_H
class Vector3
{
    public:
        Vector3();
        Vector3(float x, float y, float z);

        Vector3* add(Vector3* v);
        Vector3* sub(Vector3* v);
        Vector3* scale(float scalar);
        float dot(Vector3* v);


        float norm();

        float getX();
        float getY();
        float getZ();

    private:
        float x,y,z;
};
#endif