package com.codenow.fellowers.model.dtio.user;

import lombok.Data;

import java.io.Serializable;

@Data
public class userRegisterRequest implements Serializable {
    private static final long serialVersionUID = -8779884910782368720L;

    private String account;

    private String password;

    private String checkPassword;

}
