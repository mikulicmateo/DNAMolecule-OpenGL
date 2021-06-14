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
    void set_time(double time){
        m_time = time;
    }
    float get_radius(){
        return m_radius;
    }
    void zoom(float val){
        if(m_radius + val < 2.19 || m_radius + val > 3.5){
            m_autoZoom = false;
            return;
        }else{
            m_radius += val;
        }
    }
    bool get_autoZoom(){
        return m_autoZoom;
    }
    void set_autoZoom(bool val){
        m_autoZoom = val;
    }

private:
    bool m_Enable = false;
    double m_time = 0;
    float m_radius = 3.5;
    bool m_autoZoom = true;

};

#endif//ZADACA_ANIMATION_H
