package com.codenow.fellowers.model.dtio.user;

import lombok.Data;

import java.io.Serializable;

@Data
public class userLoginRequest implements Serializable {

    private static final long serialVersionUID =-2003865729085633211L;

    private String account;

    private String password;

}
