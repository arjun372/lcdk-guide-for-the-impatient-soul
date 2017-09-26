
#define BUFFER 16384*8

typedef struct {
  float *input;
  float *labels;
  size_t nInputs;
  size_t nLabels;
  size_t nSamples;
  const char **label_names;
} dataset;

void free_dataset(dataset *data){
  free(data->input);
  free(data->labels);
  free(data);
  return;
}

dataset *load_dataset(const char* filename, const size_t num_features, const char **labels, const size_t num_labels) {

    dataset *data = malloc(sizeof(dataset) * 1);
    if(data == NULL)
    {
      fprintf(stderr, "Could allocate memory for dataset: %s\n");
      return NULL;
    }

    data->nSamples = 0;
    data->label_names = labels;
    data->nLabels = num_labels;
    data->nInputs = num_features;

    FILE *in = fopen(filename, "r");
    if (!in) {
        printf("Could not open file: %s\n", filename);
        return NULL;
    }

    char line[BUFFER];
    /* Loop through the data to get a count. */
    while (!feof(in) && fgets(line, BUFFER, in))
    {
        (data->nSamples)++;
    }

    fseek(in, 0, SEEK_SET);
    printf("Loading %lu data points from %s\n", (data->nSamples), filename);

    /* Allocate memory for input and output data-> */
    data->input = (float *)  malloc(sizeof(float) * (data->nSamples) * data->nInputs);
    data->labels = (float *) malloc(sizeof(float) * (data->nSamples) * data->nLabels);
    if(data->input == NULL || data->labels == NULL)
    {
      fprintf(stderr, "Unable to allocate memory for dataset %s, quitting\n", filename);
      exit(1);
    }


    /* Read the file into our arrays. */
    size_t i, j, k;
    for (i = 0; i < data->nSamples; ++i)
    {
        float *p = data->input  + (i * data->nInputs);
        float *c = data->labels + (i * data->nLabels);

        fgets(line, BUFFER, in);
        char *split = strtok(line, ",");
        for (j = 0; j < data->nInputs; ++j)
        {
            p[j] = atof(split);
            split = strtok(0, ",");
            //printf("read word %f @ index %lu\n", p[j], j);
        }

        split[strlen(split)-1] = 0;
        for(k = 0; k < data->nLabels; k++)
        {
          const char* label = data->label_names[k];
          c[k] = (strcmp(split, label) == 0) ? 1.0 : 0.0;
        }
    }

    fclose(in);

    fprintf(stderr, "Successfully loaded file %s\n", filename);
    return data;
}
