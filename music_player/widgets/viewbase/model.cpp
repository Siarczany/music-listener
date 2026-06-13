#include "model.h"


void Model::add(ModelData *newData){
    data.append(newData);
}

void Model::remove(const int index){
    data.remove(index);
}

void Model::update(const int index, ModelData *newData){
    delete data[index];
    data[index] = newData;
}

int Model::count() const {
    return data.count();
}

const QVector<ModelData *> &Model::getAll() const {
    return data;
}

const ModelData *Model::get(const int index){
    return data[index];
}

Model::~Model(){
    for(auto& element : data){
        delete element;
    }
}
