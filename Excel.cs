using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Reflection;
using Microsoft.Office.Interop.Excel;
using System.Data.SqlClient;

namespace 成绩管理系统
{
    public partial class Excel : Form
    {
        public Excel()
        {
            InitializeComponent();
        }
        public bool DataSetToExcel(DataSet dataSet, bool isShowExcle) 
        {
            System.Data.DataTable dataTable = dataSet.Tables[0]; 
            int rowNumber = dataTable.Rows.Count; 

           int rowIndex = 1; 
           int colIndex = 0; 


            if (rowNumber == 0) 
            { 
                return false; 
            } 

            //建立Excel对象 
            Microsoft.Office.Interop.Excel.Application excel = new Microsoft.Office.Interop.Excel.Application(); 
            excel.Application.Workbooks.Add(true);    //新建一张excel工作簿
            excel.Visible = isShowExcle;   //是否打开该Excel文件

            //生成字段名称 
            foreach (DataColumn col in dataTable.Columns) 
            { 
                colIndex++; 
                excel.Cells[1, colIndex] = col.ColumnName; 
            } 

            //填充数据 
           foreach (DataRow row in dataTable.Rows) 
            { 
                rowIndex++; 
               colIndex = 0; 
               foreach (DataColumn col in dataTable.Columns) 
               { 
                    colIndex++; 
                  excel.Cells[rowIndex, colIndex] = row[col.ColumnName]; 
               } 
            } 

           return true; 
       }

        private void button1_Click(object sender, EventArgs e)
        {
            string connection = "SERVER=.;DATABASE=MyData;PWD=1234;UID=sa;";
            SqlConnection conn1 = new SqlConnection(connection);
            conn1.Open();

            SqlCommand cmd = new SqlCommand("select * from 课程成绩录入", conn1);
            SqlDataAdapter da = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();
            da.Fill(ds);
            DataSetToExcel(ds,true);
        }
    }







}
