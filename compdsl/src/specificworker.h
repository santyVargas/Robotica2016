/*
 *    Copyright (C) 2016 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
       \brief
       @author Aldo Rodríguez, Santiago Vargas.
*/

#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H
#include <qmat/QMatAll>
#include <genericworker.h>
#include <innermodel/innermodel.h>

#include <math.h>
#include <complex> 


class SpecificWorker : public GenericWorker
{
  
int MAX_ADVANCE = 600;
bool isVisible;

 struct Target{
  
  bool active=false;
  mutable QMutex m;
  
  QVec pose;
  
  void setActive(bool V){
    QMutexLocker ml(&m);
    active=V;
  }
  
  
  void copy(float x, float z){
    
    QMutexLocker ml(&m); 
    /*
    pose.resize(2);
    pose[0]=x;
    pose[1]=z;*/
    
    pose.resize(3);
    pose[0]=x;
    pose[1]=0;
    pose[2]=z;
  }
  
  bool isActive()
  {
    QMutexLocker ml(&m); 
    return  active;
  }
  
  QVec getPose(){
    QMutexLocker ml(&m); 
    return  pose;
  }
  
 };
 

enum class State{IDLE,INIT,GOTO,BUG};
Q_OBJECT

public:
	SpecificWorker(MapPrx& mprx);	
	~SpecificWorker();
	bool setParams(RoboCompCommonBehavior::ParameterList params);
	
	void setPick(const Pick &myPick);
	void gotoTarget(float dist);
	void esquivarCajasLaser(float dist);
	void bug();
	bool obstacle();
	bool targetAtSight();
	
	
public slots:
	void compute(); 	

private:
	Target target;
	InnerModel *innermodel;
	State state;
	RoboCompLaser::TLaserData ldata = laser_proxy->getLaserData();  //read laser data 
	RoboCompDifferentialRobot::TBaseState bState;
};

#endif

