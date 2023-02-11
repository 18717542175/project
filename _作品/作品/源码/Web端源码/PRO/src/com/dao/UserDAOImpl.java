package com.dao;

import com.bean.User;

import java.sql.SQLException;

public class UserDAOImpl extends com.dao.BaseDAO implements com.dao.UserDAO {
    @Override
    public User queryUserByUsername(String username) throws SQLException {
        String sql = "select id,username,password,email from t_user where username=?";
        return queryForOne(User.class,sql,username);
    }

    @Override
    public int saveUser(User user) throws SQLException {
        String sql = "insert into t_user(username, password, email) values(?, ?, ?)";
        return update(sql,user.getUsername(),user.getPassword(),user.getEmail());
    }

    @Override
    public User queryUserByUsernameAndPassword(String username, String password) throws SQLException {
        String sql = "select id,username,password,email from t_user where username=? and password=?";
        return queryForOne(User.class,sql,username, password);
    }
}
