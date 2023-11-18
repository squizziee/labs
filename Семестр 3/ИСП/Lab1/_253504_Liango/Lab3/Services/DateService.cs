namespace Lab3.Services;

public abstract class DateService
{
    public static string GetWeekDay(string date)
    {
        try
        {
            string[] arr = date.Split('.');
            int day = Convert.ToInt32(arr[0]);
            int month = Convert.ToInt32(arr[1]);
            int year = Convert.ToInt32(arr[2]);
            DateTime dt = new DateTime(year, month, day);
            return dt.DayOfWeek.ToString();
        } catch (Exception e)
        {
            return "?";
        }
    }

    public static string DaysTill(int day, int month, int year)
    {
        DateTime current = DateTime.Today;
        DateTime dest = new DateTime(year, month, day);
        return dest.Subtract(current).Days.ToString();
    }
}