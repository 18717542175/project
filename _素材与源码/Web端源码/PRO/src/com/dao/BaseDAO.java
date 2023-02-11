package com.dao;

import com.utils.JdbcUtils;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;

public abstract class BaseDAO {
    //使用BDutils操作数据库
    private QueryRunner queryRunner = new QueryRunner();

    /**
     * 用来执行insert/update/delete语句
     * @return 如果返回-1说明执行失败 其他表示影响的行数
     * @param sql sql语句
     * @param args 可变参数 用于填充占位符
     */
    public int update(String sql, Object...args) throws SQLException {
        Connection connection = JdbcUtils.getConnection();
        try {
            return queryRunner.update(connection, sql, args);
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }finally {
            JdbcUtils.close(connection);
        }
        return -1;
    }


    /**
     * 查询返回一个javaBean的sql语句
     * @param type 对象类型
     * @param sql sql语句
     * @param args sql对应的参数
     * @param <T> 返回的类型的泛型
     * @return
     */
    public <T> T  queryForOne(Class<T> type, String sql, Object ...args) throws SQLException {
        Connection conn = JdbcUtils.getConnection();
        try {
            return queryRunner.query(conn,sql,new BeanHandler<T>(type), args);
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }finally {
            JdbcUtils.close(conn);
        }
        return null;
    }

    /**
     * 查询返回多个javaBean的sql语句
     * @param type 对象类型
     * @param sql sql语句
     * @param args sql对应的参数
     * @param <T> 返回的类型的泛型
     * @return
     */
    public <T>List<T> queryForList(Class<T> type, String sql, Object ...args) throws SQLException {
        Connection conn = JdbcUtils.getConnection();
        try {
            return queryRunner.query(conn,sql,new BeanListHandler<>(type), args);
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }finally {
            JdbcUtils.close(conn);
        }
        return null;
    }

    /**
     * 执行返回一行一列的sql
     * @param sql sql语句
     * @param args sql参数
     * @return
     * @throws SQLException
     */
    public Object queryForSingValue(String sql, Object ...args) throws SQLException {
        Connection conn = JdbcUtils.getConnection();
        try {
            return queryRunner.query(conn,sql,new ScalarHandler(),args);
        } catch (SQLException sqlException) {
            sqlException.printStackTrace();
        }finally {
            JdbcUtils.close(conn);
        }
        return null;
    }
}
