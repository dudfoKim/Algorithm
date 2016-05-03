package knapsack01.decoder;

import java.io.File;
import java.util.*;
import org.jgap.*;
import org.jgap.data.*;
import org.jgap.impl.*;
import org.jgap.xml.XMLDocumentBuilder;
import org.jgap.xml.XMLManager;
import org.w3c.dom.Document;

/**
 * @author Ja-Hee Kim, ������
 * 0/1 knapsack ���� �ذ��� ���� ������ �˰��� ���α׷�
 * �賶������ ���������� ������ ������ �̸� �ذ��ϱ� ���� ���ڴ��� ����Ѵ�.
 * This program provides an implementation of the 0/1 knapsack problem using the genetic algorithm.
 * This genetic algorithm uses decoder for satisfying the constraints.
 */
public class Knapsack {
	
	private final static String CVS_REVISION = "$Revision: $0.1$";
	/**
	 * �� �ܰ��� ��ȭ�� ����� �������� ���� ����
	 */
	private static final int MAX_ALLOWED_EVOLUTION = 10;
	
	/**
	 * Knapsack ������ ���� ����
	 * itemWeight: �� item���� ����
	 * itemProfit: �� item���� ���Ե� ���� �̵�
	 * itemNames: �� item���� �̸�
	 */
//	public final static double[] itemWeight = {10, 5.0, 15., 20.};
//	public final static double[] itemProfit = {2, 10, 10,8};
//	public final static String[] itemName={"Carrot", "Orange", "Grape", "Banana"};
	  public final static double[] itemVolumes = {
	      50.2d, 14.8d, 27.5d, 6800.0d, 25.0d, 4.75d, 95.36d, 1500.7d, 18365.9d,
	      83571.1d};

	  /** Names of arbitrary items, only for outputting something imaginable*/
	  public final static String[] itemName = {
	      "Torch", "Banana", "Miniradio", "TV", "Gameboy", "Small thingie",
	      "Medium thingie", "Big thingie", "Huge thingie", "Gigantic thingie"};
	
	public static void main(String[] args) {
		// �賶�� ũ�⸦ �Է��Ͻÿ�.
		Scanner input = new Scanner(System.in);
		System.out.println("�賶�� �ִ� �߷���?");
		double maxWeight = input.nextDouble();
		
		// �⺻ configuration ����ϱ�
		Configuration conf = new DefaultConfiguration();
		Genotype population = null;
		
		
		//���յ� �Լ��� KnapsackPenaltyLog
		FitnessFunction myF=null;
		
		try {		
			myF=new KnapsackDecoderFitnessFn(maxWeight, itemVolumes, itemVolumes);

			conf.setFitnessFunction(myF);

			// Chromosome ���� ����
			Gene[] sampleG = new Gene[itemName.length];
			for (int i = 0 ; i < itemName.length ; i++) {
				sampleG[i] = new IntegerGene(conf, 0,itemName.length-i-1);
			}
			
			IChromosome sampleCh = new Chromosome(conf, sampleG);
			conf.setSampleChromosome(sampleCh);
			
			conf.setPopulationSize(50);
			
			// ���� ���뿡�� ��� ���� ������ ������ �����ñ�? 1.0�̸� ��ü ��
			// 1.0 ������ ��� �ʿ��� ��ŭ �������� �����Ѵ�.
			conf.setSelectFromPrevGen(.9);

			conf.setPreservFittestIndividual(true);//������ ���� ������ ������ ����
			
			population = Genotype.randomInitialGenotype(conf);
			
		} catch(Exception e){
			System.err.println(e.getMessage());
			System.exit(0);
		}
		
		IChromosome best = null;

		for(int i = 0 ; i < MAX_ALLOWED_EVOLUTION; i++ ){
			population.evolve();
			
			best = population.getFittestChromosome();
			int[] selected = ((KnapsackDecoderFitnessFn)myF).decoder(best);
			System.out.println(i+" ����: " +((KnapsackDecoderFitnessFn)myF).getTotalWeight(selected));
			System.out.println(i+" ����: " +((KnapsackDecoderFitnessFn)myF).getTotalProfit(selected));
			for(int j = 0 ; j < itemName.length ; j++)
				if(selected[j]>=1)
					System.out.println(itemName[j]);

		}
		
		// population�� XML file ���·� �����ϱ�
		DataTreeBuilder builder = DataTreeBuilder.getInstance();
		try {
			IDataCreators doc = builder.representGenotypeAsDocument(population);
			XMLDocumentBuilder docbuilder = new XMLDocumentBuilder();
			Document xmlDoc = (Document) docbuilder.buildDocument(doc);
			XMLManager.writeFile(xmlDoc, new File("knapsackJGAP.xml"));
		} catch(Exception e) {
			System.err.println(e.getMessage());
			System.exit(0);
		}
		
		best = population.getFittestChromosome();
		// ���� �� ���
		int[] selected = ((KnapsackDecoderFitnessFn)myF).decoder(best);
		System.out.println("���� ����: " +((KnapsackDecoderFitnessFn)myF).getTotalWeight(selected));
		System.out.println("���� ����: " +((KnapsackDecoderFitnessFn)myF).getTotalProfit(selected));
		for(int j = 0 ; j < itemName.length ; j++)
			if(selected[j]>=1)
				System.out.println(itemName[j]);

	}
}
