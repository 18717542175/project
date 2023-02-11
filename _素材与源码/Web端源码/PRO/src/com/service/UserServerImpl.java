package com.service;


import com.bean.User;
import com.dao.UserDAO;
import com.dao.UserDAOImpl;


import java.sql.SQLException;

public class UserServerImpl implements UserServer{
    //实现UserDAO类
    private UserDAO userDAO = new UserDAOImpl();


    /**
     * 用户注册
     * @param user
     * @throws SQLException
     */
    @Override
    public void registUser(User user) throws SQLException {
        userDAO.saveUser(user);
    }

    /**
     * 用户登录
     * @param user
     * @return
     */
    @Override
    public User login(User user) {
        try {
            return userDAO.queryUserByUsernameAndPassword(user.getUsername(),user.getPassword());
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }
        return null;
    }

    /**
     * 检查用户名是否存在
     * @param username
     * @return
     */
    @Override
    public boolean existUsername(String username) {
        try {
            //如果查询为null则表示不存在 否者表示用户名已存在
            if (userDAO.queryUserByUsername(username) == null){
                return false;
            }
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        };
        return true;
    }
}
