package com.codenow.fellowers.service;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.codenow.fellowers.model.dtio.user.UserTagsRequest;
import com.codenow.fellowers.model.dtio.user.userLoginRequest;
import com.codenow.fellowers.model.dtio.user.userRegisterRequest;
import com.codenow.fellowers.model.entity.User;
import com.baomidou.mybatisplus.extension.service.IService;
import com.codenow.fellowers.model.vo.user.UserVO;

import javax.servlet.http.HttpServletRequest;
import java.util.List;

/**
 * @author axliu Mogullzr
 */
public interface UserService extends IService<User> {

    /**
     * search user by tags
     *
     * @param userTagsRequest userTagsRequest
     * @return List<UserVO>
     */
    List<UserVO> searchUserByTags(UserTagsRequest userTagsRequest, HttpServletRequest request);

    /**
     * get user vo
     *
     * @param user user
     * @return UserVO
     */
    UserVO getUserVO(User user);

    /**
     *获取登录用户信息
     *
     * @param httpServletRequest request
     * @return User
     */
    User getLoginUser(HttpServletRequest httpServletRequest);
    /**
     * search user by tags memory
     *
     * @param userTagsRequest userTagsRequest
     * @param request         request
     * @return List<UserVO>
     */
    List<UserVO> searchUserByTagsMemory(UserTagsRequest userTagsRequest, HttpServletRequest request);

    QueryWrapper<User> getQueryWrapper(UserTagsRequest userTagsRequest, HttpServletRequest request);

    /**
     * 进行用户注册
     *
     * @param request request
     * @return 用户id
     */
    long userRegister(userRegisterRequest request);

    /**
     * 记性用户登录
     *
     * @param httpServletRequest 前端请求
     * @return 脱敏用户信息
     */
    UserVO userLogin(userLoginRequest userLoginRequest, HttpServletRequest httpServletRequest);

    /**
     * 进行退出
     *
     * @param httpServletRequest request
     * @return boolean
     */
    boolean userLogout(HttpServletRequest httpServletRequest);
}
