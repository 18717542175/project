package com.bean;

import java.io.PrintWriter;

public class Iot {
    private String id;
    private String N;
    private String P;
    private String K;
    private String W;
    private String S;

    public Iot() {
        super();
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        return super.equals(obj);
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
    }

    @Override
    public String toString() {
        return "Iot{" +
                "id=" + id +
                ", N='" + N + '\'' +
                ", P='" + P + '\'' +
                ", K='" + K + '\'' +
                ", W='" + W + '\'' +
                ", S='" + S + '\'' +
                '}';
    }

    public Iot(String id, String n, String p, String k, String w, String s) {

        this.id = id;
        N = n;
        P = p;
        K = k;
        W = w;
        S = s;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setN(String n) {
        N = n;
    }

    public void setP(String p) {
        P = p;
    }

    public void setK(String k) {
        K = k;
    }

    public void setW(String w) {
        W = w;
    }

    public void setS(String s) {
        S = s;
    }

    public String getId() {
        return id;
    }

    public String getN() {
        return N;
    }

    public String getP() {
        return P;
    }

    public String getK() {
        return K;
    }

    public String getW() {
        return W;
    }

    public String getS() {
        return S;
    }
}
