package com.briup.jdbc;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.briup.bean.Student;



//ѧ�������ݿ⣩������
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
	
	
	//1.�����ݿ��ȡ����ѧ����Ϣ��ʾ
	public void checkAll(){
		Connection conn = null;
		Statement stmt = null;
		ResultSet rs =null;
		try{
			//1.ע������
			Class.forName(driver);
			//2.��ȡ���ݿ⣬���Ӷ���
			conn = DriverManager.getConnection(ur1, userName, passWd);
			
			//3.��ȡStatement���������
			stmt = conn.createStatement();
			//4.ͨ��Statement���������ִ��sql���
			String sql = "select * from tab1;";
			rs = stmt.executeQuery(sql);
			//5.����ǲ�ѯ��䣬�����ؽ����
			//����� �α���ʽ����beforFrist afterLast
			while(rs.next()){
				//���ձ�Ż�ȡ
				int id = rs.getInt(1);
				//�������ֻ�ȡ
				String name = rs.getString("name");
				//����
				int age = rs.getInt(3);
				//�Ա�
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
	
	//2.���һ��ѧ���������ݿ����棩
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
			//1.ע��
			Class.forName(driver);
			//2.ʹ��DriverManager����ȡ���ݿ����Ӷ���
			conn = DriverManager.getConnection(ur1, userName, passWd);
			//3.��ȡStatement��������
			String sql= "insert into tab1 values(?,?,?,?);";
			pstmt =conn.prepareStatement(sql);
			pstmt.setInt(1, id);
			pstmt.setInt(3, age);
			pstmt.setString(2, name);
			pstmt.setString(4, gender);
			
			//4.����PrepareStatementȥִ��sql���
			num = pstmt.executeUpdate();
			
			if(num !=0){
				System.out.println("�ɹ����"+num+"������");
			}
			else{
				System.out.println("���ʧ��");
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
	
	//3.ɾ������
	public boolean deleteStudebtById(int id){
		Connection conn = null;
		PreparedStatement pstmt = null;
		int num = 0;
		try {
			//1.ע��driver
			Class.forName(driver);
			
			
			//2.ʹ��DriverManager����ȡ���ݿ����Ӷ���
			conn = DriverManager.getConnection(ur1, userName, passWd);
			
			
			//3.��ȡStatement��������
			String sql= "delete from tab1 where id = ?;";
			pstmt =conn.prepareStatement(sql);
			pstmt.setInt(1, id);
			
			//4.����PrepareStatementȥִ��sql���
			num = pstmt.executeUpdate();
			if(num !=0){
				System.out.println("�ɹ�ɾ��"+num+"������");
				return true;
			}
			else{
				System.out.println("ɾ��ʧ��");
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
	//4.�޸����ݿ�ѧ����Ϣ
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
				System.out.println("�ɹ��޸�"+num+"������");
			}
			else{
				System.out.println("�޸�ʧ��");
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
		System.out.println("**1.�鿴ѧ����Ϣ**");
		System.out.println("**2.����ѧ����Ϣ**");
		System.out.println("**3.ɾ��ѧ����Ϣ**");
		System.out.println("**4.�޸�ѧ����Ϣ**");
		System.out.println("**5.�˳���ǰϵͳ**");
		System.out.println("*****************");
	}
}
