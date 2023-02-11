package com.service;

import com.bean.User;

import java.sql.SQLException;

public interface UserServer {
    /**
     * 注册用户
     * @param user
     */
    public void registUser(User user) throws SQLException;

    /**
     * 登录
     * @param user
     * @return 返回是null表示登录失败 返回有值表示登陆失败
     */
    public User login(User user);

    /**
     * 检查用户名是否可用
     * @param username
     * @return 返回true表示用户已存在 false表示用户名可用
     */
    public boolean existUsername(String username);
}
