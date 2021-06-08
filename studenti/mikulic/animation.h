//
// Created by mateo on 06. 06. 2021..
//

#ifndef ZADACA_ANIMATION_H
#define ZADACA_ANIMATION_H

class Animation{
public:
    Animation(){}
    bool get_status(){
        return m_Enable;
    }
    void enable_animation(bool enable){
        m_Enable = enable;
    }
    double get_time(){
        return m_time;
    }
    double set_time(double time){
        m_time = time;
    }

private:
    bool m_Enable = false;
    double m_time = 0;

};

#endif//ZADACA_ANIMATION_H
