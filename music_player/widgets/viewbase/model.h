#pragma once

#include <QVector>

class ModelData
{

};

class Model
{
public:
    void add(ModelData* newData){
        data.append(newData);
    }
    void remove(const int index){
        data.remove(index);
    }
    void update(const int index, ModelData* newData){
        delete data[index];
        data[index] = newData;
    }
    int count() const {
        return data.count();
    }
    const QVector<ModelData*>& getAll() const {
        return data;
    }
    const ModelData* get(const int index){
        return data[index];
    }
    ~Model(){
        for(auto& element : data){
            delete element;
        }
    }
private:
    QVector<ModelData*> data;
};
