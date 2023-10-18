CREATE DATABASE IF NOT EXISTS `fellowers` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

USE `fellowers`;

-- 用户信息表
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`
(
    `uuid`        bigint                                  NOT NULL AUTO_INCREMENT COMMENT 'id',
    `account`     varchar(256) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '账号',
    `password`    varchar(512) COLLATE utf8mb4_unicode_ci NOT NULL COMMENT '密码',
    `username`    varchar(256) COLLATE utf8mb4_unicode_ci          DEFAULT NULL COMMENT '名称',
    `avatar`      varchar(2048) COLLATE utf8mb4_unicode_ci         DEFAULT NULL COMMENT '头像地址',
    `tags`        varchar(2048) COLLATE utf8mb4_unicode_ci         DEFAULT NULL COMMENT '标签',
    `email`       varchar(512) COLLATE utf8mb4_unicode_ci          DEFAULT NULL COMMENT '邮箱',
    `phone`       varchar(128) COLLATE utf8mb4_unicode_ci          DEFAULT NULL COMMENT '电话',
    `gender`      varchar(20) COLLATE utf8mb4_unicode_ci           DEFAULT NULL COMMENT '性别',
    `profile`     text COLLATE utf8mb4_unicode_ci COMMENT '简介',
    `role`        varchar(256) COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT 'user' COMMENT '用户角色：user/admin/ban',
    `create_time` datetime                                NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `update_time` datetime                                NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
    `is_delete`   tinyint                                 NOT NULL DEFAULT '0' COMMENT '是否删除',
    PRIMARY KEY (`uuid`),
    UNIQUE KEY `account` (`account`)
) ENGINE = InnoDB
  AUTO_INCREMENT = 8
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci COMMENT ='用户信息表';

-- 标签表
DROP TABLE IF EXISTS `tag`;
CREATE TABLE `tag`
(
    `id`          bigint   NOT NULL AUTO_INCREMENT COMMENT 'id',
    `tag_name`    varchar(256) COLLATE utf8mb4_unicode_ci DEFAULT NULL COMMENT '标签名',
    `uid`         bigint                                  DEFAULT NULL COMMENT '用户id',
    `parent_id`   bigint                                  DEFAULT NULL COMMENT '父标签id',
    `is_parent`   tinyint  NOT NULL                       DEFAULT '0' COMMENT '是否是父标签：0 不是，1 是',
    `create_time` datetime NOT NULL                       DEFAULT CURRENT_TIMESTAMP COMMENT '创建时间',
    `update_time` datetime NOT NULL                       DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '更新时间',
    `is_delete`   tinyint  NOT NULL                       DEFAULT '0' COMMENT '是否删除',
    PRIMARY KEY (`id`),
    UNIQUE KEY `idx_tag_name` (`tag_name`) COMMENT '标签索引',
    KEY `idx_user_id` (`uid`) COMMENT '用户id索引'
) ENGINE = InnoDB
  AUTO_INCREMENT = 8
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_unicode_ci COMMENT ='标签表'