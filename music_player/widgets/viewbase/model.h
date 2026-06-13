#pragma once

#include <QVector>

// Base class for Data that the model will hold
class ModelData
{

};

// Holds and maganages the base class of data
class Model
{
public:
    void add(ModelData* newData);
    void remove(const int index);
    void update(const int index, ModelData* newData);
    // returns number of elements in the model
    int count() const;
    const QVector<ModelData*>& getAll() const;
    const ModelData* get(const int index);
    ~Model();
private:
    QVector<ModelData*> data;
};
