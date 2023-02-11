<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>智慧农业可视化大屏</title>
    <%
        //获取服务器的Ip地址
        String basePath = request.getScheme() //请求方式
                + "://"
                +request.getServerName() //Ip地址
                +":"
                +request.getServerPort()   //端口号
                +request.getContextPath()      //工程路径
                +"/";
    %>
    <base href="<%=basePath%>"/>
<%--    <%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>--%>
<%--    <link rel="stylesheet" href="<c:url value="css/index.css"></c:url>"/>--%>
    <link rel="stylesheet" href="page/user/css/index.css"/>
    <script type="text/javascript" src="js/index.js"></script>
    <script type="text/javascript" src="js/echarts.min.js"></script>
    <script type="text/javascript" src="js/jquery-1.7.2.js"></script>
</head>

<body>
    <div class="box"></div>
</body>
<!--头部的盒子-->
    <header>
        <h1>智慧农业可视化大屏</h1>
        <div class="showTime"></div>
        <!--时间显示脚本-->
        <script>
            var t = null;
            t = setTimeout(time, 1000);//開始运行
            function time() {
                clearTimeout(t);//清除定时器
                dt = new Date();
                var y = dt.getFullYear();
                var mt = dt.getMonth() + 1;
                var day = dt.getDate();
                var h = dt.getHours();//获取时
                var m = dt.getMinutes();//获取分
                var s = dt.getSeconds();//获取秒
                document.querySelector(".showTime").innerHTML = y + "年" + mt + "月" + day + "-" + h + "时" + m + "分" + s + "秒";
                t = setTimeout(time, 1000); //设定定时器，循环运行
            }
        </script>
    </header>
    <!--页面主题-->
    <section class="mainbox">
        <!--左侧-->
        <div class="column">
            <!--图一-->
            <div class="panel bar" >
                <h2>土壤温度(℃)</h2>
                <div class="chart">

                </div>
                <div class="panel-footer">

                </div>
            </div>
            <!--图二-->
            <div class="panel line" >
                <h2>土壤湿度(%)
<%--                    <a href="javascript:;">2020</a>--%>
<%--                    <a href="javascript:;">2021</a>--%>
                </h2>
                <div class="chart">

                </div>
                <div class="panel-footer">

                </div>
            </div>
            <!--图三-->
            <div class="panel ple" >
                <h2>各作物占比</h2>
                <div class="chart">

                </div>
                <div class="panel-footer">

                </div>
            </div>
        </div>
        <div class="column">
            <!--中间模块制作-->
            <div class="no">
                <div class="no-hd">
                    <ur>
                        <li>1</li>
                        <li>1</li>
                    </ur>
                </div>
                <div class="no-bd">
                    <ur>
                        <li>设备总数</li>
                        <li>在线设备</li>
                    </ur>
                </div>
            </div>

            <!--视频传输模块-->
            <div class="map">
                <div class="map0">
                    <iframe class="iframe"   src="http://192.168.43.125:8080/?action=stream"  name="pi"
                            ></iframe>

                    <div class="contr">
                        <div class="contr1">
                            <br>
                            <br>
                            <button class="openWater" onclick="function x() {

                            }">打开水泵</button>
                            <button class="closeWater" onclick="function x() {

                            }">关闭水泵</button>
                            <button class="update">刷新</button>
                        </div>

                        <div class="contr2">

                        </div>
                </div>
                </div>
            </div>



        </div>
        </div>
        <div class="column">
            <!--图一-->
            <div class="panel bar2" >
                <h2>磷(P)含量</h2>
                <div class="chart">

                </div>
                <div class="panel-footer">

                </div>
            </div>
            <!--图二-->
            <div class="panel line2">
                <h2>氮(N)含量</h2>
                <div class="chart">

                </div>
                <div class="panel-footer">

                </div>
            </div>
            <!--图三-->
            <div class="panel ple2" >
                <h2>钾(K)含量</h2>
                <div class="chart">

                </div>
                <div class="panel-footer">

                </div>
            </div>
        </div>
    </section>
    <!--引入flexible.js文件 屏幕自动适配 24-->

    <script src="lib/jquery-1.7.2.js"></script>
    <script src="page/user/js/echarts.min.js"></script>
    <script src="page/user/js/index.js"></script>
    <script src="page/user/js/flexible.js"></script>
    <script src="page/user/js/china.js"></script>
</html>