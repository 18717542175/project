package com.test;

import com.bean.User;
import org.junit.Test;
import com.service.UserServerImpl;

import java.sql.SQLException;

import static org.junit.Assert.*;

public class UserServerTest {

    UserServerImpl server = new UserServerImpl();
    @Test
    public void registUser() throws SQLException {
        server.registUser(new User(9,"laaa","789798","7894798"));
    }

    @Test
    public void login() {
        User wang = server.login(new User(8, "wang", "123123", "123123"));
        System.out.println(wang);
    }

    @Test
    public void existUsername() {
        boolean existUsername = server.existUsername("wang");
        System.out.println(existUsername);
    }
}