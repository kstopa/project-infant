#include "CoordinateSystem.h"
#include <math.h>

CoordinateSystem::CoordinateSystem()
{
    dx = 0.0;
    dy = 0.0;
    alfa = 0.0;
    scale_x = 1.0;
    scale_y = 1.0;
}

CoordinateSystem::CoordinateSystem(Vector* base)
{
    dx = base->P0.X;
    dy = base->P0.Y;
    alfa = base->Angle();
    scale_x = base->Module();
    scale_y = base->Module();
}

CoordinateSystem::CoordinateSystem(Vector* base_x, Vector* base_y)
{
    dx = base_x->P0.X;
    dy = base_y->P0.Y;
    alfa = base_x->Angle();
    scale_x = base_x->Module();
    scale_y = base_y->Module();
}

//
// Cambia el sistema de coordendas original al del vector de definicion. Es decir al sistema del objeto desde la captura.
//
Vector* CoordinateSystem::ConvertToSystem(Vector* v)
{
    Vector* v_ = new Vector();
    // Se realiza la traslación y traslación en relación al vector que define el sistema de coordendas.
    v_->P0.X = (v->P0.X - dx) * cos(alfa) + (v->P0.Y - dy) * sin(alfa);
    v_->P0.Y = -(v->P0.X - dx) * sin(alfa) + (v->P0.Y - dy) * cos(alfa);
    v_->P1.X = (v->P1.X - dx) * cos(alfa) + (v->P1.Y - dy) * sin(alfa);
    v_->P1.Y = -(v->P1.X - dx) * sin(alfa) + (v->P1.Y - dy) * cos(alfa);
    // Se escala en relación al modulo del vector base (%) que define el sistema de coordendas.
    v_->P0.X = (v_->P0.Distance()*100/scale_x) * cos(v_->P0.Angle());
    v_->P0.Y = (v_->P0.Distance()*100/scale_y) * sin(v_->P0.Angle());
    v_->P1.X = (v_->P1.Distance()*100/scale_x) * cos(v_->P1.Angle());
    v_->P1.Y = (v_->P1.Distance()*100/scale_y) * sin(v_->P1.Angle());
    return v_;
}


VectorCollection* CoordinateSystem::ConvertToSystem(VectorCollection* V)
{
    VectorCollection* v_trans = new VectorCollection();
    for (int nV = 0; nV < V->size(); nV++)
    {
        Vector *aux = ConvertToSystem(&V->at(nV));
        v_trans->Add(*aux);
    }
    return v_trans;
}

CoordinateSystem::~CoordinateSystem()
{
    //dtor
}
