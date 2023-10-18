package com.codenow.fellowers.model.vo.user;

import lombok.Data;

import java.io.Serializable;
import java.util.List;

@Data
public class UserVO implements Serializable {

    private Long uuid;

    /**
     * 账号
     */
    private String account;


    /**
     * 名称
     */
    private String username;

    /**
     * 头像地址
     */
    private String avatar;

    /**
     * 标签
     */
    private List<String> tags;

    /**
     * 邮箱
     */
    private String email;

    /**
     * 电话
     */
    private String phone;

    /**
     * 性别
     */
    private String gender;

    /**
     * 简介
     */
    private String profile;
    /**
     * 权利
     */
    private String role;

    private static final long serialVersionUID = 1L;
}
