using Logitech;
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace CommunityDoctor
{
    public partial class HosDocProfile : System.Web.UI.Page
    {


        SqlCommand cmd = new SqlCommand();
        SqlConnection con = new SqlConnection();
        SqlDataAdapter sda = new SqlDataAdapter();
        DataSet ds = new DataSet();
        SqlCommandBuilder builder;

        DataOperation db = new DataOperation();
        protected void Page_Load(object sender, EventArgs e)
        {

            if (Session["User2"] == null)
            {
                Response.Redirect("HosDocLogin.aspx");
            }
            else
                con.ConnectionString = "Data Source=DESKTOP-F9ITDCA;Initial Catalog=CommunityDoctor;Integrated Security=True";
            con.Open();
            showdata();



            //con = new SqlConnection();

            string sql = "SELECT * FROM Admission";
            ds = new DataSet();
            sda = new SqlDataAdapter(sql, con);
            sda.Fill(ds);
            builder = new SqlCommandBuilder(sda);
            GridView1.DataSource = ds.Tables[0];
            count();

            if (!IsPostBack)
            {
                this.loadgrid();

            }

        }
        //seat available

        public void count()
        {
            //string str = @"Data Source=DESKTOP-BEAKPLU\\SQLEXPRESS;Initial Catalog=CommunityDoctor;Integrated Security=True";
            lblbook.Text = ds.Tables[0].Rows.Count.ToString();

            int values = Int32.Parse(lblbook.Text);
            lblseat.Text = (40 - values).ToString();
        }

        public void loadgrid()
        {
            string query = @"SELECT * FROM Admission";
            GridView1.DataSource = db.GetDatatable(query);
            GridView1.DataBind();
        }














        public void showdata()
        {
            cmd.CommandText = "select * from HosDoctor where username='" + Session["user2"] + "' ";
            cmd.Connection = con;
            sda.SelectCommand = cmd;
            sda.Fill(ds);
            lblhocode.Text = ds.Tables[0].Rows[0]["HO_Code"].ToString();
            lblname.Text = ds.Tables[0].Rows[0]["username"].ToString();
            lbladdress.Text = ds.Tables[0].Rows[0]["Address"].ToString();
            lblphone.Text = ds.Tables[0].Rows[0]["Phone"].ToString();
            lblemail.Text = ds.Tables[0].Rows[0]["Email"].ToString();
            lblquali.Text = ds.Tables[0].Rows[0]["qualification"].ToString();
            //lblhocode.Text = ds.Tables[0].Rows[0]["_Code"].ToString();
        }

        protected void Button2_Click(object sender, EventArgs e)
        {

            Session["user2"] = lblhocode.Text;

            Response.Redirect("PatientAdmission.aspx");
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            Session["user2"] = null;
            Response.Redirect("HosDocLogin.aspx");
        }




        protected void GridView1_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
            Label lblID = (Label)GridView1.Rows[e.RowIndex].FindControl("Label1");
            string query = @"DELETE FROM [dbo].[Admission]
                            WHERE AdmitId =" + lblID.Text;
            if (db.executequery(query) == 1)
            {
                loadgrid();
                Response.Redirect(Request.Url.AbsoluteUri);
            }

        }
    }
}
