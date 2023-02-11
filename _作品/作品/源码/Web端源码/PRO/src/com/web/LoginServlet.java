package com.web;

import com.bean.User;
import com.utils.WebUtils;
import com.service.UserServerImpl;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        //获取Web界面输入的信息
//        User user = WebUtils.copyParamToBean(req.getParameterMap(), new User());//*/**/*/*/

        UserServerImpl userServer = new UserServerImpl();

        String username = req.getParameter("username");
        String password = req.getParameter("password");
        System.out.println(username);
        System.out.println(password);

        User login = userServer.login(new User(null, username, password, null));
        System.out.println(login);

        if (login == null){
            System.out.println("没有该用户");
            req.setAttribute("msg","没有该用户 请先注册");
            //如果没有该用户 则页面不发生变化
            req.getRequestDispatcher("/page/user/login.jsp").forward(req,resp);
        }else {
            //有过登录成功则跳转到登录成功页面
            req.getRequestDispatcher("/page/user/success.jsp").forward(req,resp);
        }
    }
}
