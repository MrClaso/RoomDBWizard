myfile << "package se.lortboan.worksschedule;\n";
myfile << "\n";
myfile << "import android.content.Context;\n";
myfile << "import android.content.Intent;\n";
myfile << "import android.view.LayoutInflater;\n";
myfile << "import android.view.View;\n";
myfile << "import android.view.ViewGroup;\n";
myfile << "import android.widget.LinearLayout;\n";
myfile << "import android.widget.TextView;\n";
myfile << "\n";
myfile << "import androidx.lifecycle.LiveData;\n";
myfile << "import androidx.lifecycle.ViewModelProvider;\n";
myfile << "import androidx.recyclerview.widget.RecyclerView;\n";
myfile << "\n";
myfile << "import java.util.List;\n";
myfile << "\n";
myfile << "public class WorkDayListAdapter extends RecyclerView.Adapter<WorkDayListAdapter.WorkDayViewHolder> {\n";
myfile << "\n";
    myfile << "private Context mContext;\n";
myfile << "\n";
myfile << "\n";
    myfile << "class WorkDayViewHolder extends RecyclerView.ViewHolder{\n";
        myfile << "private final TextView dateTextView;\n";
        myfile << "private final TextView startTimeTextView;\n";
        myfile << "private final TextView endTimeTextView;\n";
        myfile << "private final TextView weekDayTextView;\n";
        myfile << "private final LinearLayout linearLayoutDay;\n";
myfile << "\n";
        myfile << "private WorkDayViewHolder(View itemView) {\n";
            myfile << "super(itemView);\n";
            myfile << "dateTextView = itemView.findViewById(R.id.textViewDate);\n";
            myfile << "startTimeTextView = itemView.findViewById(R.id.textViewStartTime);\n";
            myfile << "endTimeTextView = itemView.findViewById(R.id.textViewEndTime);\n";
            myfile << "weekDayTextView = itemView.findViewById(R.id.textViewWeekDay);\n";
            myfile << "linearLayoutDay = itemView.findViewById(R.id.linearLayoutDay);\n";
        myfile << "}\n";
myfile << "\n";
    myfile << "}\n";
myfile << "\n";
    myfile << "private final LayoutInflater mInflater;\n";
    myfile << "private List<WorkDay> mWorkDay; // Cached copy of workdays\n";
myfile << "\n";
myfile << "\n";
    myfile << "WorkDayListAdapter(Context context) {\n";
myfile << "\n";
        myfile << "this.mContext = context;\n";
        myfile << "mInflater = LayoutInflater.from(context);\n";
    myfile << "}\n";
myfile << "\n";
    myfile << "@Override\n";
    myfile << "public WorkDayViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {\n";
        myfile << "View itemView = mInflater.inflate(R.layout.recyclerview_item, parent, false);\n";
        myfile << "return new WorkDayViewHolder(itemView);\n";
    myfile << "}\n";
myfile << "\n";
    myfile << "@Override\n";
    myfile << "public void onBindViewHolder(WorkDayViewHolder holder, int position) {\n";
myfile << "\n";
myfile << "/*    Den här utkommenterade snutten reagerar på klick på en rad.\n";
      myfile << "paket är info skickat till intent\n";
myfile << "\n";
        myfile << "holder.itemView.setOnClickListener(v -> {\n";
            myfile << "Intent intent = new Intent(mContext, ViewWorkDay.class);\n";
            myfile << "WorkDay aWorkday = mWorkDay.get(position);\n";
            myfile << "intent.putExtra(\"view_workday\", paket);\n";
myfile << "\n";
            myfile << "mContext.startActivity(intent);\n";
        myfile << "});\n";
myfile << "*/\n";
myfile << "\n";
        myfile << "if (mWorkDay != null) {\n";
            myfile << "WorkDay current = mWorkDay.get(position);\n";
            myfile << "holder.dateTextView.setText(current.getDate());\n";
            myfile << "holder.weekDayTextView.setText(finalDay);\n";
            myfile << "holder.startTimeTextView.setText(String.valueOf(current.getStartTime()));\n";
            myfile << "holder.endTimeTextView.setText(String.valueOf(current.getEndTime()));\n";
myfile << "\n";
        myfile << "} else {\n";
            myfile << "// Covers the case of data not being ready yet.\n";
            myfile << "holder.dateTextView.setText(\"No data to show\");\n";
        myfile << "}\n";
    myfile << "}\n";
myfile << "\n";
    myfile << "void setWorkDays(List<WorkDay> workDays){\n";
        myfile << "mWorkDay = workDays;\n";
        myfile << "notifyDataSetChanged();\n";
    myfile << "}\n";
myfile << "\n";
    myfile << "// getItemCount() is called many times, and when it is first called,\n";
    myfile << "// mWorkDay has not been updated (means initially, it's null, and we can't return null).\n";
    myfile << "@Override\n";
    myfile << "public int getItemCount() {\n";
        myfile << "if (mWorkDay != null)\n";
            myfile << "return mWorkDay.size();\n";
        myfile << "else return 0;\n";
    myfile << "}\n";
myfile << "}\n";
