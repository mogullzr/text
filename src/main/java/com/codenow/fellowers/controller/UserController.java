package com.codenow.fellowers.controller;

import com.codenow.fellowers.common.BaseResponse;
import com.codenow.fellowers.common.ResultUtils;
import com.codenow.fellowers.model.dtio.user.userLoginRequest;
import com.codenow.fellowers.model.dtio.user.userRegisterRequest;
import com.codenow.fellowers.model.dtio.user.UserTagsRequest;
import com.codenow.fellowers.model.vo.user.UserVO;
import com.codenow.fellowers.service.UserService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import java.util.List;

/**
 * author axliu Mogullzr
 */
@RestController
@RequestMapping("/user")
@Slf4j
public class UserController {

    @Resource
    private UserService userService;

    @GetMapping("/get/login")
    public BaseResponse<UserVO> getLoginUser(HttpServletRequest request) {
        return ResultUtils.success(userService.getUserVO(userService.getLoginUser(request)));
    }

    @PostMapping("/search")
    public BaseResponse<List<UserVO>> searchUserByTags(@RequestBody UserTagsRequest userTagsRequest, HttpServletRequest request) {
        return ResultUtils.success(userService.searchUserByTags(userTagsRequest, request));
    }

    @PostMapping("/register")
    public BaseResponse<Long> userRegister(@RequestBody userRegisterRequest userRegisterRequest) {
        return ResultUtils.success(userService.userRegister(userRegisterRequest));
    }

    @PostMapping("/login")
    public BaseResponse<UserVO> userLogin(@RequestBody userLoginRequest userLoginRequest, HttpServletRequest httpServletRequest) {
        return ResultUtils.success(userService.userLogin(userLoginRequest, httpServletRequest));

    }

    @PostMapping("/logout")
    public BaseResponse<Boolean> userLogout(HttpServletRequest httpServletRequest) {
        return ResultUtils.success(userService.userLogout(httpServletRequest));
    }
}
