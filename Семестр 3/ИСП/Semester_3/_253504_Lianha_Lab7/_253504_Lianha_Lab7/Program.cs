using _253504_Lianha_Lab7.Domain;

//var result = IntegralSolver.Solve();
//Console.WriteLine(result);
Progress progress = new(1) { Delay = 1 };
var solver1 = new IntegralSolver(3);
solver1.NotifyProgressListeners += (step) =>
{
	progress.Update(step);
};
solver1.NotifyCompletionListeners += (result) =>
{
	Console.WriteLine($"\n{result}");
};
solver1.Solve();

var solver2 = new IntegralSolver(2);
solver2.NotifyCompletionListeners += (result) =>
{
	Console.WriteLine(result);
};

Thread[] threads = new Thread[5];

for (int i = 0; i < 5; i++)
{
	threads[i] = new Thread(solver2.Solve);
	threads[i].Start();
}

/*var thread1 = new Thread(() =>
{
	solver1.Solve();
	Console.WriteLine($"\nLow priority thread : {IntegralSolver.Result}");
})
{
	Priority = ThreadPriority.Highest
};

var thread2 = new Thread(() =>
{
	solver1.Solve();
	Console.WriteLine($"\nHigh priority thread : {IntegralSolver.Result}");
})
{
	Priority = ThreadPriority.Lowest
};
thread1.Start();
thread2.Start();*/