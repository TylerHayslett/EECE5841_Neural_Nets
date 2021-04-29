function [lines] = extract_data(file_name)
%EXTRACT_DATA Summary of this function goes here

% Format for lines of data
l_format = ['[' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ',' '%f' ']'];

fileID = fopen(file_name,'r');
z = 1;

for i = (1:6749)
    %disp(tline)
    tline = fgetl(fileID);
    if ~isempty(tline)
        if tline(1) == '[' 
          lines(z,:) = sscanf(tline, l_format);
          z = z + 1;
        end
    end
end

fclose(fileID);

end

