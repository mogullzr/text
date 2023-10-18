package com.codenow.fellowers;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan("com.codenow.fellowers.mapper")
public class FellowersApplication {

    public static void main(String[] args) {
        SpringApplication.run(FellowersApplication.class, args);
    }

}
