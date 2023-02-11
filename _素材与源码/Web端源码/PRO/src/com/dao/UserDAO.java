package com.dao;

import com.bean.User;

import java.sql.SQLException;

public interface UserDAO {
    /**
     * 根据用户名查询用户信息
     * @param username
     * @return 返回null没有用户
     */
    public User queryUserByUsername(String username) throws SQLException;

    /**
     * 保存用户信息
     * @param user
     * @return
     */
    public int saveUser(User user) throws SQLException;

    /**
     * 根据用户名和密码查询用户信息
     * @param username
     * @param password
     * @return
     */
    public User queryUserByUsernameAndPassword(String username, String password) throws SQLException;
}
