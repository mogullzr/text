package com.codenow.fellowers.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.codenow.fellowers.common.ErrorCode;

import com.codenow.fellowers.model.dtio.user.UserTagsRequest;
import com.codenow.fellowers.model.dtio.user.userLoginRequest;
import com.codenow.fellowers.model.dtio.user.userRegisterRequest;
import com.codenow.fellowers.model.entity.User;
import com.codenow.fellowers.model.vo.user.UserVO;
import com.codenow.fellowers.service.UserService;
import com.codenow.fellowers.mapper.UserMapper;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.codenow.fellowers.execption.BusinessException;
import lombok.extern.slf4j.Slf4j;
import org.apache.commons.collections4.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.util.DigestUtils;

import javax.servlet.http.HttpServletRequest;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

import static com.codenow.fellowers.contants.UserConstant.USER_LOGIN_STATE;

/**
 * @author axliu Mogullzr
 */
@Service
@Slf4j
public class UserServiceImpl extends ServiceImpl<UserMapper, User> implements UserService {

    private final static Gson GSON = new Gson();

    private static final String SALT = "xiaoyu";

    @Override
    public List<UserVO> searchUserByTags(UserTagsRequest userTagsRequest, HttpServletRequest request) {
        QueryWrapper<User> queryWrapper = this.getQueryWrapper(userTagsRequest, request);
        List<String> tagNameList = userTagsRequest.getTagsNameList();
        // 拼接 and 条件 like '%java%' and like '%python%'
        for (String tagName : tagNameList) {
            queryWrapper = queryWrapper.like("tags", tagName);
        }
        List<User> users = this.baseMapper.selectList(queryWrapper);
        // 脱敏
        users.forEach(this::getUserVO);
        return users.stream().map(this::getUserVO).collect(Collectors.toList());
    }

    @Override
    public UserVO getUserVO(User user) {
        if (user == null) {
            return null;
        }
        UserVO userVO = new UserVO();
        BeanUtils.copyProperties(user, userVO);
        userVO.setTags(GSON.fromJson(user.getTags(), new TypeToken<List<String>>() {
        }.getType()));
        return userVO;
    }

    @Override
    public User getLoginUser(HttpServletRequest httpServletRequest) {
        if (httpServletRequest == null) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR);
        }
        Object userobj = httpServletRequest.getSession().getAttribute(USER_LOGIN_STATE);
        User currentUser = (User) userobj;
        if (userobj == null || currentUser.getUuid() == null) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR);
        }
        return currentUser;
    }

    @Override
    public List<UserVO> searchUserByTagsMemory(UserTagsRequest userTagsRequest, HttpServletRequest request) {
        QueryWrapper<User> queryWrapper = this.getQueryWrapper(userTagsRequest, request);
        List<String> tagNameList = userTagsRequest.getTagsNameList();
        // 查询出所有的用户
        List<User> userList = this.baseMapper.selectList(queryWrapper);
        // 在内存中判断是否包含要求的标签
        return userList.stream().filter(user -> {
            String tagStr = user.getTags();
            if (StringUtils.isBlank(tagStr)) {
                return false;
            }
            Set<String> tags = GSON.fromJson(tagStr, new TypeToken<Set<String>>() {
            }.getType());
            for (String tagName : tagNameList) {
                if (!tags.contains(tagName)) {
                    return false;
                }
            }
            return true;
        }).map(this::getUserVO).collect(Collectors.toList());
    }

    @Override
    public QueryWrapper<User> getQueryWrapper(UserTagsRequest userTagsRequest, HttpServletRequest request) {
        if (userTagsRequest == null || request == null) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR);
        }
        List<String> tagNameList = userTagsRequest.getTagsNameList();
        if (CollectionUtils.isEmpty(tagNameList)) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR);
        }
        return new QueryWrapper<>();
    }

    @Override
    public long userRegister(userRegisterRequest userRegisterRequest) {
        if (userRegisterRequest == null) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR, "注册信息不能为空");
        }
        // 提取前端数据
        String userAccount = userRegisterRequest.getAccount();
        String userPassword = userRegisterRequest.getPassword();
        String checkPassword = userRegisterRequest.getCheckPassword();

        if (StringUtils.isAnyBlank(userAccount, userPassword, checkPassword) || StringUtils.isAllBlank(userAccount, userPassword, checkPassword)) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR, "注册信息不能为空");
        }

        if (userAccount.length() < 4) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR, "账户必须大于4位");
        }


        if (!userPassword.equals(checkPassword)) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR, "两次输入密码不一致");
        }

        if (userPassword.length() < 8) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR, "密码必须大于8位");
        }

        // 线程同步的原因是保证当前用户的账户的唯一性
        synchronized (userAccount.intern()) {
            // 账户不能重复
            QueryWrapper<User> queryWrapper = new QueryWrapper<>();
            queryWrapper.eq("account", userAccount);
            long count = this.baseMapper.selectCount(queryWrapper);
            if (count > 0) {
                throw new BusinessException(ErrorCode.PARAMS_ERROR, "用户已存在");
            }

            // 密码进行加密
            String encryptPassword = DigestUtils.md5DigestAsHex((userPassword + SALT).getBytes());
            // 将数据输入到数据库里面去
            User user = new User();
            user.setAccount(userAccount);
            user.setPassword(encryptPassword);
            boolean result = this.save(user);
            if (!result) {
                throw new BusinessException(ErrorCode.PARAMS_ERROR, "注册失败");
            }
            return user.getUuid();
        }
    }

    @Override
    public UserVO userLogin(userLoginRequest userLoginRequest, HttpServletRequest httpServletRequest) {
        if (userLoginRequest == null || httpServletRequest == null) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR, "信息不能为空");
        }

        // 将前端获取数据取出来
        String account = userLoginRequest.getAccount();
        String password = userLoginRequest.getPassword();
        if (StringUtils.isAnyBlank(account, password) || StringUtils.isAnyBlank(account, password)) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR, "登录信息不能为空");
        }


        // 进行加密
        String encryptPassword = DigestUtils.md5DigestAsHex((password + SALT).getBytes());
        // 查询用户是否存在
        QueryWrapper<User> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("account", account);
        queryWrapper.eq("password", encryptPassword);
        User user = this.baseMapper.selectOne(queryWrapper);
        if (user == null) {
            log.info("user login failed, userAccount cannot match userPassword");
            throw new BusinessException(ErrorCode.PARAMS_ERROR, "用户不存在或密码错误");
        }

        // 记录用户的登录状态
        httpServletRequest.getSession().setAttribute(USER_LOGIN_STATE, user);
        return this.getUserVO(user);
    }

    @Override
    public boolean userLogout(HttpServletRequest httpServletRequest) {
        if (httpServletRequest == null) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR);
        }
        if (httpServletRequest.getSession().getAttribute(USER_LOGIN_STATE) == null) {
            throw new BusinessException(ErrorCode.PARAMS_ERROR, "未登录");
        }
        httpServletRequest.getSession().removeAttribute(USER_LOGIN_STATE);
        return true;
    }
}




