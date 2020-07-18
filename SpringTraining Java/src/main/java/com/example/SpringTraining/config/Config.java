package com.example.SpringTraining.config;

import com.example.SpringTraining.model.Wheel;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.Arrays;
import java.util.List;
import java.util.SortedMap;

@Configuration
public class Config {

    @Bean("FrontLeft")
    public Wheel frontLeftWheel(){
        return new Wheel();
    }

    @Bean("FrontRight")
    public Wheel frontRightWheel(){
        return new Wheel();
    }

    @Bean("BackLeft")
    public Wheel backLeftWheel(){
        return new Wheel();
    }

    @Bean("BackRight")
    public Wheel backRightWheel(){
        return new Wheel();
    }

    @Bean("wheels")
    public List<Wheel> wheelsOfCar(){
        return Arrays.asList(frontLeftWheel(), frontRightWheel(), backLeftWheel(), backRightWheel());
    }

}
