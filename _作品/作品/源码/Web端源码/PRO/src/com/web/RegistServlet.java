package com.web;

import com.bean.User;
import com.test.UserServerTest;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;

import com.service.*;

public class RegistServlet extends HttpServlet {
    //用户注册
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {

        System.out.println("注册");
        UserServer userServer = new UserServerImpl();

        String username = req.getParameter("username");
        String password = req.getParameter("password");
        String repwd = req.getParameter("repwd");
        String email = req.getParameter("email");
        String code = req.getParameter("code");

        System.out.println(username);
        System.out.println(password);
        System.out.println(repwd);
        System.out.println(email);
        System.out.println(code);
        //        2.检查验证码
        if ("abcde".equalsIgnoreCase(code))
        {
            if (userServer.existUsername(username)){
                System.out.println("用户名不可用");
                req.getRequestDispatcher("/page/user/regist.jsp").forward(req,resp);
            }else {     //此时用户名不存在
                System.out.println("用户名可用");
                try {
                    //往数据库添加数据
                    userServer.registUser(new User(null, username, password, email));
                } catch (SQLException sqlException) {
                    sqlException.printStackTrace();
                }
                req.getRequestDispatcher("/page/user/success.jsp").forward(req,resp);
            };
        }else { //如果验证码不正确跳到注册页面
            System.out.println("验证码错误！");
            req.getRequestDispatcher("/page/user/regist.jsp").forward(req,resp);
        }
    }
}