package com.briup.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.briup.bean.Student;



//学生（数据库）操作类
public class StudentDao {
	private String driver;
	private String ur1;
	private String userName;
	private String passWd;
	
	public StudentDao() {
		driver = "com.mysql.jdbc.Driver";
		ur1 = "jdbc:mysql://localhost:3306/"+"sms6?characterEncoding=utf8";
		userName = "root";
		passWd = "ybx520@@@";
	}
	
	
	//1.从数据库获取所有学生信息显示
	public void checkAll(){
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs =null;
		try{
			//1.注册驱动
			Class.forName(driver);
			//2.获取数据库，连接对象
			conn = DriverManager.getConnection(ur1, userName, passWd);
			
			//3.获取Statement或子类对象
			stmt = conn.createStatement();
			//4.通过Statement或子类对象执行sql语句
			String sql = "select * from tab1;";
			rs = stmt.executeQuery(sql);
			//5.如果是查询语句，处理返回结果集
			//结果集 游标形式出现beforFrist afterLast
			while(rs.next()){
				//按照编号获取
				int id = rs.getInt(1);
				//按照名字获取
				String name = rs.getString("name");
				//年龄
				int age = rs.getInt(3);
				//性别
				String gender = rs.getString("gender");
				System.out.println("id: "+id+" name: "+name+" age: "+age+" gender: "+gender);
			}
		}catch(Exception e){
			e.printStackTrace();
		}finally{
			try{
				if(rs != null){
					rs.close();
				}
				if(stmt != null){
					stmt.close();
				}
				if(conn != null){
					conn.close();
				}
				
			}catch(SQLException e){
				e.printStackTrace();
			}
		}
	}
	
	//2.添加一个学生（到数据库里面）
	//insert into tab1 values(?,?,?,?);
	public void addStudent(Student s){
		int id = s.getId();
		String name =s.getName();
		int age = s.getAge();
		String gender = s.getGender();
		Connection conn = null;
		PreparedStatement pstmt = null;
		int num = 0;
		try {
			//1.注册
			Class.forName(driver);
			//2.使用DriverManager来获取数据库连接对象
			conn = DriverManager.getConnection(ur1, userName, passWd);
			//3.获取Statement或其子类
			String sql= "insert into tab1 values(?,?,?,?);";
			pstmt =conn.prepareStatement(sql);
			pstmt.setInt(1, id);
			pstmt.setInt(3, age);
			pstmt.setString(2, name);
			pstmt.setString(4, gender);
			
			//4.利用PrepareStatement去执行sql语句
			num = pstmt.executeUpdate();
			
			if(num !=0){
				System.out.println("成功添加"+num+"条数据");
			}
			else{
				System.out.println("添加失败");
			}
		} catch (Exception e) {
			e.printStackTrace();
			// TODO: handle exception
		}finally{
			try{
				if(pstmt != null){
					pstmt.close();
				}
				if(conn != null){
					conn.close();
				}
				
			}catch(SQLException e){
				e.printStackTrace();
			}
		}
		
	} 
	
	//3.删除功能
	public boolean deleteStudebtById(int id){
		Connection conn = null;
		PreparedStatement pstmt = null;
		int num = 0;
		try {
			//1.注册driver
			Class.forName(driver);
			
			
			//2.使用DriverManager来获取数据库连接对象
			conn = DriverManager.getConnection(ur1, userName, passWd);
			
			
			//3.获取Statement或其子类
			String sql= "delete from tab1 where id = ?;";
			pstmt =conn.prepareStatement(sql);
			pstmt.setInt(1, id);
			
			//4.利用PrepareStatement去执行sql语句
			num = pstmt.executeUpdate();
			if(num !=0){
				System.out.println("成功删除"+num+"条数据");
				return true;
			}
			else{
				System.out.println("删除失败");
				return false;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}finally{
			try{
				if(pstmt != null){
					pstmt.close();
				}
				if(conn != null){
					conn.close();
				}
				
			}catch(SQLException e){
				e.printStackTrace();
			}
		}

		if(num ==0){
			return true;
		}
		else{
			return false;
		}
	}
	//4.修改数据库学生信息
	public void changeStudentById(int id,Student s){
		//update tab1 set name=?,age=? gender=? where id=?;
		int num = 0;
		String name =s.getName();
		int age = s.getAge();
		String gender = s.getGender();
		Connection conn = null;
		PreparedStatement pstmt = null;
		
		try {
			Class.forName(driver);
			conn = DriverManager.getConnection(ur1, userName, passWd);
			String sql="update tab1 set name=?,age=?,gender=?where id=?;";
			pstmt =conn.prepareStatement(sql);
			pstmt.setInt(4, id);
			pstmt.setInt(2, age);
			pstmt.setString(1, name);
			pstmt.setString(3, gender);
			
			num = pstmt.executeUpdate();
			if(num !=0){
				System.out.println("成功修改"+num+"条数据");
			}
			else{
				System.out.println("修改失败");
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			// TODO: handle exception
		}finally{
			try{
				if(pstmt != null){
					pstmt.close();
				}
				if(conn != null){
					conn.close();
				}
				
			}catch(SQLException e){
				e.printStackTrace();
			}
		}
	}
	
	
	
	
	public void view(){
		System.out.println("*****************");
		System.out.println("**1.查看学生信息**");
		System.out.println("**2.增加学生信息**");
		System.out.println("**3.删除学生信息**");
		System.out.println("**4.修改学生信息**");
		System.out.println("**5.退出当前系统**");
		System.out.println("*****************");
	}
}
