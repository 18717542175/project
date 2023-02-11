package com.dao;

import com.bean.Iot;

import java.sql.SQLException;

public class IotDAOImpl extends com.dao.BaseDAO implements IotDAO {
    @Override
    public int saveIotData(Iot iot) throws SQLException {
        String sql = "insert into iotData(id,N,P,K,W,S) values(?,?,?,?,?,?)";
        return update(sql,iot.getId(), iot.getN(),iot.getP(), iot.getK(), iot.getW(), iot.getS());
    }
}
