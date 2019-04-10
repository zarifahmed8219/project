using Logitech;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace CommunityDoctor
{
    public partial class PatientAdmission : System.Web.UI.Page
    {
        SqlCommand cmd = new SqlCommand();
        DataOperation db = new DataOperation();
        protected void Page_Load(object sender, EventArgs e)
        {


            txthocode.Text = Session["user2"].ToString();
            //lblusername.Text = Session["user2"].ToString();
            loadgrid();
            //loadgrid2();
            if (!this.IsPostBack)
            {
                this.loadgrid2();
            }
        }

       protected void Select_Click(object sender,EventArgs e)
        {
            int Patientid = Convert.ToInt32((sender as LinkButton).CommandArgument);

            string query = @"SELECT CM_Code,Pa_Code,Pa_name,Pa_address,Pa_phone,Pa_email FROM Patient WHERE Pa_ID = '" + Patientid + "'";
            DataTable table = db.GetDatatable(query);
            txtcocode.Text = table.Rows[0]["CM_Code"].ToString();
            txtpacode.Text = table.Rows[0]["Pa_Code"].ToString();
            txtpaname.Text = table.Rows[0]["Pa_name"].ToString();
            txtpaAddress.Text = table.Rows[0]["Pa_address"].ToString();
            txtpaphone.Text = table.Rows[0]["Pa_phone"].ToString();
            txtpaemail.Text = table.Rows[0]["Pa_email"].ToString();
            //txtpacode.Text = table.Rows[0]["Pa_Code"].ToString();


        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            String query = @"SELECT * FROM Patient WHERE Patient.Pa_ID = ('" + TextBox1.Text + "')";
            GridView1.DataSource = db.GetDatatable(query);
            GridView1.DataBind();
            TextBox1.Text = String.Empty;
        }

        public void loadgrid()
        {
            string query = @"SELECT * FROM Patient";
            GridView1.DataSource = db.GetDatatable(query);
            GridView1.DataBind();
        }

        protected void GridView1_PageIndexChanging(object sender, GridViewPageEventArgs e)
        {
            GridView1.PageIndex = e.NewPageIndex;
            this.loadgrid();
        }

        protected void Button4_Click(object sender, EventArgs e)
        {
            Calendar1.Visible = true;
        }

        protected void Calendar1_SelectionChanged(object sender, EventArgs e)
        {
            txtsdnt.Text = (Calendar1.SelectedDate.ToShortDateString());
            Calendar1.Visible = false;
        }

        protected void Button5_Click(object sender, EventArgs e)
        {
            Calendar2.Visible = true;
        }

        protected void Calendar2_SelectionChanged(object sender, EventArgs e)
        {
            txtednt.Text = (Calendar2.SelectedDate.ToShortDateString());
            Calendar2.Visible = false;

        }

        protected void Button2_Click(object sender, EventArgs e)
        {
            string query = @"INSERT INTO [dbo].[Admission]
           ([HosDocCode]
           ,[ComDocCode]
           ,[PatientCode]
           ,[PatientName]
           ,[PatientAddress]
           ,[PatientPhone]
           ,[PatientEmail]
           ,[Diagnosis]
           ,[Report]
           ,[Treatment]
           ,[StartDate]
           ,[EndDate])
     VALUES
           ('" + txthocode.Text + "','" + txtcocode.Text + "','" + txtpacode.Text + "','" + txtpaname.Text + "','" + txtpaAddress.Text + "','" + txtpaphone.Text + "','" + txtpaemail.Text + "','" + Dropdiagnosis.Text + "','" + Dropreport.Text + "','" + Droptreatment.Text + "','" + txtsdnt.Text + "','" + txtednt.Text + "' )";
            if (db.executequery(query) == 1)
            {
                Response.Write("<script>alert('Save Successfully!')</script>");
            }
            else
            {
                Response.Write("<script>alert('input error!')</script>");
            }

            txtcocode.Text = "";
            txtpacode.Text = "";
            txtpaname.Text = "";
            txtpaAddress.Text = "";
            txtpaphone.Text = "";
            txtpaemail.Text = "";
            txtsdnt.Text = "";
            txtednt.Text = "";
        }

        protected void Button3_Click(object sender, EventArgs e)
        {
            string query = @"INSERT INTO[dbo].[Discharge]
           ([HosDocCode]
           ,[ComDocCode]
           ,[PatientCode]
           ,[PatientName]
           ,[PatientAddress]
           ,[PatientPhone]
           ,[PatientEmail]
           ,[Diagnosis]
           ,[Report]
           ,[Treatment]
           ,[StartDate]
           ,[EndDate])
     VALUES
           ('" + txthocode.Text + "','" + txtcocode.Text + "','" + txtpacode.Text + "','" + txtpaname.Text + "','" + txtpaAddress.Text + "','" + txtpaphone.Text + "','" + txtpaemail.Text + "','" + Dropdiagnosis.Text + "','" + Dropreport.Text + "','" + Droptreatment.Text + "','" + txtsdnt.Text + "','" + txtednt.Text + "' )";

            if (db.executequery(query) == 1)
            {
                Response.Write("<script>alert('Save Successfully!')</script>");
            }
            else
            {
                Response.Write("<script>alert('input error!')</script>");
            }
            lbldischarge.Visible = true;
            //GridView2.Visible = true;

            txtcocode.Text = "";
            txtpacode.Text = "";
            txtpaname.Text = "";
            txtpaAddress.Text = "";
            txtpaphone.Text = "";
            txtpaemail.Text = "";
            txtsdnt.Text = "";
            txtednt.Text = "";

        }

        protected void GridView2_RowDeleting(object sender, GridViewDeleteEventArgs e)
        {
            Label lblID = (Label)GridView2.Rows[e.RowIndex].FindControl("Label13");
            string query = @"DELETE FROM [dbo].[Discharge]
                            WHERE AdmitId =" + lblID.Text;
            if (db.executequery(query) == 1)
            {
                loadgrid2();
            }
        }

        public void loadgrid2()
        {
            string query = @"SELECT * FROM Discharge";
            GridView2.DataSource = db.GetDatatable(query);
            GridView2.DataBind();

        }

        protected void GridView2_RowEditing(object sender, GridViewEditEventArgs e)
        {
            GridView2.EditIndex = e.NewEditIndex;
            this.loadgrid2();

        }

        protected void GridView2_RowCancelingEdit(object sender, GridViewCancelEditEventArgs e)
        {
            GridView2.EditIndex = -1;
            this.loadgrid2();

        }

        protected void GridView2_RowUpdating(object sender, GridViewUpdateEventArgs e)
        {

            GridViewRow row = GridView2.Rows[e.RowIndex];
            int AdmitID = Convert.ToInt32(GridView2.DataKeys[e.RowIndex].Values[0]);
            string HosDoctorCode = (row.FindControl("HosDocCode") as TextBox).Text;
            string comDoctorCode = (row.FindControl("ComDocCode") as TextBox).Text;
            string PatientCode = (row.FindControl("PatientCode") as TextBox).Text;
            string PatientName = (row.FindControl("PatientName") as TextBox).Text;
            string PatientAddress = (row.FindControl("PatientAddress") as TextBox).Text;
            string PatientPhone = (row.FindControl("PatientPhone") as TextBox).Text;
            string PatientEmail = (row.FindControl("PatientEmail") as TextBox).Text;
            string Diagnosis = (row.FindControl("Diagnosis") as TextBox).Text;
            string Report = (row.FindControl("Report") as TextBox).Text;
            string Treatment = (row.FindControl("Treatment") as TextBox).Text;
            string StartDate = (row.FindControl("StartDate") as TextBox).Text;
            string EndDate = (row.FindControl("EndDate") as TextBox).Text;
            string query = "UPDATE Discharge SET HosDocCode=@HosDocCode, ComDocCode=@ComDocCode, PatientCode=@PatientCode, PatientName=@PatientName, PatientAddress=@PatientAddress, PatientPhone=@PatientPhone, PatientEmail=@PatientEmail, Diagnosis=@Diagnosis, Report=@Report, Treatment=@Treatment, StartDate=@StartDate, EndDate=@EndDate WHERE AdmitId=@AdmitId";
            string constr = ConfigurationManager.ConnectionStrings["DefaultConnection"].ConnectionString;
            using (SqlConnection con = new SqlConnection(constr))
            {
                using (SqlCommand cmd = new SqlCommand(query))
                {
                    cmd.Parameters.AddWithValue("@AdmitId", AdmitID);
                    cmd.Parameters.AddWithValue("@HosDocCode", HosDoctorCode);
                    cmd.Parameters.AddWithValue("@ComDocCode", comDoctorCode);
                    cmd.Parameters.AddWithValue("@PatientCode", PatientCode);
                    cmd.Parameters.AddWithValue("@PatientName", PatientName);
                    cmd.Parameters.AddWithValue("@PatientAddress", PatientAddress);
                    cmd.Parameters.AddWithValue("@PatientPhone", PatientPhone);
                    cmd.Parameters.AddWithValue("@PatientEmail", PatientEmail);
                    cmd.Parameters.AddWithValue("@Diagnosis", Diagnosis);
                    cmd.Parameters.AddWithValue("@Report", Report);
                    cmd.Parameters.AddWithValue("@Treatment", Treatment);
                    cmd.Parameters.AddWithValue("@StartDate", StartDate);
                    cmd.Parameters.AddWithValue("@EndDate", EndDate);
                    cmd.Connection = con;
                    con.Open();
                    cmd.ExecuteNonQuery();
                    con.Close();

                }
            }
            GridView2.EditIndex = -1;
            this.loadgrid2();

        }

        protected void Button7_Click(object sender, EventArgs e)
        {
            Session["user2"] = null;
            Response.Redirect("HosDocLogin.aspx");
        }

        protected void Button6_Click(object sender, EventArgs e)
        {
            Session["user2"] = null;
            Response.Redirect("Default.aspx");
        }


    }
}
