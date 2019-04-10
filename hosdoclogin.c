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
    public partial class HosDocHome : System.Web.UI.Page
    {

        SqlCommand cmd = new SqlCommand();
        SqlConnection con = new SqlConnection();
        SqlDataAdapter sda = new SqlDataAdapter();
        DataSet ds = new DataSet();
        protected void Page_Load(object sender, EventArgs e)
        {

            if (Session["user2"] != null)
            {
                Response.Redirect("ComDocProfile.aspx");
            }
            else
                con.ConnectionString = "Data Source=DESKTOP-F9ITDCA;Initial Catalog=CommunityDoctor;Integrated Security=True";
            con.Open();

        }

        protected void Button4_Click(object sender, EventArgs e)
        {
            string user2 = txthousername.Text.Trim();
            cmd.CommandText = "select * from HosDoctor where username='" + txthousername.Text + "' and password ='" + txthopass.Text + "' ";
            cmd.Connection = con;
            sda.SelectCommand = cmd;
            sda.Fill(ds, "HosDoctor");
            if (ds.Tables[0].Rows.Count > 0)
            {
                Session["user2"] = user2;
                Response.Redirect("HosDocProfile.aspx");


            }
            else
            {
                ScriptManager.RegisterStartupScript(this, this.GetType(), "Message", "alert('Something Gono Wrong');", true);
            }
        }

        protected void Button3_Click(object sender, EventArgs e)
        {
            Response.Redirect("Default.aspx");
        }


    }
}
