
results = extract_data('sweep_results.txt');
rand_results = extract_data('sweep_results_rand.txt');

error = results(11:11:end, :);
error_rand = rand_results(11:11:end, :);
